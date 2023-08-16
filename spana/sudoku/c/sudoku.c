#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int SudGrid[9][9];

int FindFreeNum(int x, int y)
{
	int quad_x = x - (x % 3);
	int quad_y = y - (y % 3);

	int num;
	int xx, yy;
	int tries = 0;
	while (1) {
		if (tries++ > 500) return -1;
		num = (rand() % 9) + 1;
		int found = 0;
		// check X axis
		for (xx = 0; xx < 9 && !found; xx++) {
			if (SudGrid[xx][y] == num) {
				found = 1;
			}
		}
		// check Y axis
		for (yy = 0; yy < 9 && !found; yy++) {
			if (SudGrid[x][yy] == num) {
				found = 1;
			}
		}
		// check quad
		for (yy = quad_y; yy < quad_y + 3 && !found; yy++) {
			for (xx = quad_x; xx < quad_x + 3 && !found; xx++) {
				if (SudGrid[xx][yy] == num) {
					found = 1;
				}
			}
		}
		if (!found) {
			break;
		}
	}

	return num;
}

void PrintGrid()
{
	int x, y;

	for (y = 0; y < 9; y++) {
		if (y % 3 == 0) {
			printf("|------|------|------|");
			printf("\n");
		}
		for (x = 0; x < 9; x++) {
			if (x % 3 == 0) {
				printf("|");
			}
			if (SudGrid[x][y] == 0) {
				printf(". ");
				continue;
			}
			printf("%d ", SudGrid[x][y]);
		}
		printf("|\n");
	}
	printf("|------|------|------|\n");
	printf("\n");
}

void MakeSudoku(int start_moves)
{
	int x, y;

	int attempts = 0;
	while (1) {
		if (attempts++ > 5000) {
			// failed, clean this up later so it never happens
			printf("Failed to make puzzle\n");
			return;
		}
		int done = 1;
		memset(SudGrid, 0, sizeof(SudGrid));
		for (y = 0; y < 9 && done; y++) {
			for (x = 0; x < 9 && done; x++) {
				SudGrid[x][y] = FindFreeNum(x, y);
				if (SudGrid[x][y] < 0) {
					done = 0;
				}
			}
		}
		if (done) {
			break;
		}
	}

	// solution
	PrintGrid();

	// puzzle
	int start = 9 * 9 - start_moves;
	while (start > 0) {
		for (y = 0; y < 9 && start > 0; y++) {
			for (x = 0; x < 9 && start > 0; x++) {
				if (SudGrid[x][y] == 0) {
					continue;
				}
				if (!(rand() % 5)) {
					SudGrid[x][y] = 0;
					start--;
				}
			}
		}
	}
	PrintGrid();

	// debug
	// printf("%d tries\n", attempts);
}

int main(int argc, char **argv)
{
	srand(time(NULL));

	MakeSudoku(20);

	return 0;
}
