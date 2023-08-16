#ifndef __MAIN_H__
#define __MAIN_H__

/**********************************
* Defines
**********************************/

enum {
	PIXEL_RED,
	PIXEL_GREEN,
	PIXEL_BLUE,
	PIXEL_ORANGE,
	PIXEL_YELLOW,
	PIXEL_PURPLE,
	NUM_PIXCOLS
};

#define GRID_WIDTH 12
#define GRID_HEIGHT 12

#define SCREEN_WIDTH (GRID_WIDTH * 32)
#define SCREEN_HEIGHT (GRID_HEIGHT * 32)

/**********************************
* Externs
**********************************/

extern int Puzzle[GRID_WIDTH][GRID_HEIGHT];
extern int PuzzOld[GRID_WIDTH][GRID_HEIGHT];

/**********************************
* Prototypes
**********************************/

void MakePuzzle();
void dbgprintf(char *fmt,...); // lazy, just for now
void OpenGLDraw(int, int);
void ChangePuzzle(int col);

#endif /* __MAIN_H__ */
