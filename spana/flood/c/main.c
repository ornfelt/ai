#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "main.h"

int PuzzMoves;
int Puzzle[GRID_WIDTH][GRID_HEIGHT];
int PuzzFlags[GRID_WIDTH][GRID_HEIGHT];

// debug
int PuzzOld[GRID_WIDTH][GRID_HEIGHT];

int CalcScore()
{
	int size = GRID_WIDTH * GRID_HEIGHT;
	int factor = 10000 / size;

	int score = 10000 - (factor * PuzzMoves);
	if (score < 100) {
		score = 100;
	}
	return score;
}

void MakePuzzle()
{
	int i, j;

	PuzzMoves = 0;

	for (i = 0; i < GRID_WIDTH; i++) {
		for (j = 0; j < GRID_HEIGHT; j++) {
			Puzzle[i][j] = rand() % NUM_PIXCOLS;
		}
	}
}

// Recursively step through all identical colors and fill them
void FloodColor(int x, int y, int col)
{
	PuzzFlags[x][y] = 1;

	// left
	if (x - 1 >= 0) {
		if (Puzzle[x - 1][y] == col && PuzzFlags[x - 1][y] == 0) {
			//PuzzFlags[x - 1][y] = 1;
			FloodColor(x - 1, y, col);
		}
	}
	// right
	if (x + 1 < GRID_WIDTH) {
		if (Puzzle[x + 1][y] == col && PuzzFlags[x + 1][y] == 0) {
			//PuzzFlags[x + 1][y] = 1;
			FloodColor(x + 1, y, col);
		}
	}
	// top
	if (y - 1 >= 0) {
		if (Puzzle[x][y - 1] == col && PuzzFlags[x][y - 1] == 0) {
			//PuzzFlags[x][y - 1] = 1;
			FloodColor(x, y - 1, col);
		}
	}
	// bottom
	if (y + 1 < GRID_HEIGHT) {
		if (Puzzle[x][y + 1] == col && PuzzFlags[x][y + 1] == 0) {
			//PuzzFlags[x][y + 1] = 1;
			FloodColor(x, y + 1, col);
		}
	}
}

void ChangePuzzle(int col)
{
	PuzzMoves++;

	// debug
	memcpy(PuzzOld, Puzzle, sizeof(PuzzOld));

	memset(PuzzFlags, 0, sizeof(PuzzFlags));

	int orig = Puzzle[0][0];
	int i, j;

	FloodColor(0, 0, orig);

	// for (i = 0; i < GRID_WIDTH; i++) {
		// for (j = 0; j < GRID_HEIGHT; j++) {
			// if (PuzzFlags[i][j] == 1) {
				// FloodColor(i, j, orig);
				// // restart search
				// i = 0;
				// j = 0;
			// }
		// }
	// }

	for (i = 0; i < GRID_WIDTH; i++) {
		for (j = 0; j < GRID_HEIGHT; j++) {
			if (PuzzFlags[i][j] != 0) {
				Puzzle[i][j] = col;
			}
		}
	}

	int won = 1;
	for (i = 0; i < GRID_WIDTH; i++) {
		for (j = 0; j < GRID_HEIGHT; j++) {
			if (Puzzle[i][j] != col) {
				won = 0;
			}
		}
	}

	if (won) {
		// OpenGL is poor for handling fonts, so for now just print
		// text to terminal instead of the window buffer
#if defined(_MSC_VER) || defined(_WIN32)
		dbgprintf("You won! With %d moves, score %d\n", PuzzMoves, CalcScore());
#else
		printf("You won! With %d moves, score %d\n", PuzzMoves, CalcScore());
#endif
	}
}

void DrawAlphaBox(int X, int Y, int W, int H, int col)
{
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	switch (col) {
	case PIXEL_RED: glColor4ub(255, 0, 0, 0x80); break;
	case PIXEL_GREEN: glColor4ub(0, 255, 0, 0x80); break;
	case PIXEL_BLUE: glColor4ub(0, 0, 255, 0x80); break;
	case PIXEL_ORANGE: glColor4ub(255, 128, 0, 0x80); break;
	case PIXEL_YELLOW: glColor4ub(255, 255, 0, 0x80); break;
	case PIXEL_PURPLE: glColor4ub(128, 0, 255, 0x80); break;
	}

	glBegin(GL_TRIANGLE_FAN);
	glVertex2i(X, Y);
	glVertex2i(X, Y+H);
	glVertex2i(X+W, Y+H);
	glVertex2i(X+W, Y);	
	glEnd();

	//glDisable(GL_BLEND);
}

void OpenGLDraw(int x, int y)
{
	glClear(GL_COLOR_BUFFER_BIT);

	int i, j;

	for (i = 0; i < GRID_WIDTH; i++) {
		for (j = 0; j < GRID_HEIGHT; j++) {
			DrawAlphaBox(i * 32, j * 32, 32, 32, Puzzle[i][j]);
		}
	}

	glFlush();
}
