#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "res/resource.h"
#include "main.h"

#define APPNAME "Pixel Flood"

/*
* Windows specific code to get the window up and running,
* create an OpenGL instance, and handle input
*/

HDC sghDC;
HGLRC sghRC;
HWND ghMainWnd;
HINSTANCE ghInst;

int MouseX;
int MouseY;

BOOL gbRunApp;

void dbgprintf(char *fmt,...)
{
    static HANDLE dbg = NULL;
    char    out [ 256 ];
    DWORD  len;
    va_list vlist;

    if (dbg == NULL)
    {
        AllocConsole();
        dbg =  GetStdHandle(STD_OUTPUT_HANDLE);
        if (dbg == NULL)
            return;         
    }
    
    va_start(vlist, fmt);
    wvsprintf(out, fmt, vlist);
    WriteConsole(dbg, out, strlen(out), &len, NULL);
}

void DoTestChar(WPARAM wParam)
{
	switch (wParam) {
	case '1':
		ChangePuzzle(PIXEL_RED);
		break;
	case '2':
		ChangePuzzle(PIXEL_GREEN);
		break;
	case '3':
		ChangePuzzle(PIXEL_BLUE);
		break;
	case '4':
		ChangePuzzle(PIXEL_ORANGE);
		break;
	case '5':
		ChangePuzzle(PIXEL_YELLOW);
		break;
	case '6':
		ChangePuzzle(PIXEL_PURPLE);
		break;
	case 'n':
		MakePuzzle();
		break;
	case 'z':
		// undo last move for testing (debug)
		memcpy(Puzzle, PuzzOld, sizeof(PuzzOld));
		break;
	}
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_DESTROY:
		gbRunApp = FALSE;
		PostQuitMessage(0);
		return 0;
	case WM_CHAR:
		DoTestChar(wParam);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			gbRunApp = FALSE;
		}
		break;
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		MouseX = LOWORD(lParam);
		MouseY = HIWORD(lParam);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

HWND OpenGLWindow()
{
	HWND hWnd;
	WNDCLASSEXA wcex;

	memset(&wcex, 0, sizeof(wcex));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW|CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = ghInst;
	wcex.hIcon = LoadIcon(ghInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(0, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = APPNAME;
	wcex.lpszClassName = APPNAME;
	//wcex.hIconSm = (HICON)LoadImage(ghInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	RegisterClassEx(&wcex);
	DWORD dwWindowWidth   = SCREEN_WIDTH  + GetSystemMetrics( SM_CXFIXEDFRAME ) * 2;
	DWORD dwWindowHeight  = SCREEN_HEIGHT + GetSystemMetrics( SM_CYFIXEDFRAME ) * 2 + GetSystemMetrics( SM_CYCAPTION );
	RECT r;
	GetClientRect(GetDesktopWindow(), &r);
	int X = (r.right - dwWindowWidth) >> 1;
	if ( X < 0 )
		X = 0;
	int Y = (r.bottom - dwWindowHeight) >> 1;
	if ( Y < 0 )
		Y = 0;
	hWnd = CreateWindowEx(
			0,
			APPNAME,
			APPNAME,
			WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX & ~WS_MAXIMIZEBOX,
			X,
			Y,
			dwWindowWidth,
			dwWindowHeight,
			NULL,
			NULL,
			ghInst,
			NULL);
	if ( !hWnd )
		MessageBox(NULL, "Unable to create main window", "Error", MB_OK);
	return hWnd;
}

static void OpenGLSetupPixel()
{
    int pf;
	HDC hDC;
    PIXELFORMATDESCRIPTOR pfd;

	hDC = GetDC(ghMainWnd);

    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize        = sizeof(pfd);
    pfd.nVersion     = 1;
    pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
    pfd.iPixelType   = PFD_TYPE_RGBA;
    pfd.cColorBits   = 32;

    pf = ChoosePixelFormat(hDC, &pfd);
    if (pf == 0) {
	MessageBox(NULL, "ChoosePixelFormat() failed:  "
		   "Cannot find a suitable pixel format.", "Error", MB_OK); 
	return;
    } 
 
    if (SetPixelFormat(hDC, pf, &pfd) == FALSE) {
	MessageBox(NULL, "SetPixelFormat() failed:  "
		   "Cannot set format specified.", "Error", MB_OK);
	return;
    } 

    DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	ReleaseDC(ghMainWnd, hDC);
}

void InitOpenGL()
{
	OpenGLSetupPixel();

    sghDC = GetDC(ghMainWnd);
    sghRC = wglCreateContext(sghDC);
    wglMakeCurrent(sghDC, sghRC);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
}

void FreeOpenGL()
{
    wglMakeCurrent(NULL, NULL);
    ReleaseDC(ghMainWnd, sghDC);
    wglDeleteContext(sghRC);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	ghInst = hInstance;
	ghMainWnd = OpenGLWindow();
	if(ghMainWnd == NULL) {
		return 0;
	}

	ShowWindow(ghMainWnd, SW_SHOWNORMAL);
	UpdateWindow(ghMainWnd);

	InitOpenGL();

	MouseX = SCREEN_WIDTH / 2;
	MouseY = SCREEN_HEIGHT / 2;

	srand(time(NULL));
	MakePuzzle();

	gbRunApp = TRUE;
	while(gbRunApp) {
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message != WM_QUIT) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		OpenGLDraw(MouseX, MouseY);
		// Prevent CPU frying
		Sleep(1);
	}

	FreeOpenGL();

	return 0;
}
