package main

import (
	"fmt"
	"math/rand"
	"time"
	"unsafe"
	"github.com/galaxyhaxz/go-learn/clegacy"
)

var SudGrid [9][9]int

// brute-force the next number in the grid
func FindFreeNum(x, y int) int {
	quad_x := x - (x % 3)
	quad_y := y - (y % 3)

	var num int
	var xx, yy int
	var tries int
	tries = 0
	for {
		tries++
		if tries > 500 {
			return -1
		}
		num = rand.Intn(9) + 1
		var found int
		found = 0
		// check X axis
		for xx = 0; xx < 9 && found == 0; xx++ {
			if SudGrid[xx][y] == num {
				found = 1
			}
		}
		// check Y axis
		for yy = 0; yy < 9 && found == 0; yy++ {
			if SudGrid[x][yy] == num {
				found = 1
			}
		}
		// check quad
		for yy = quad_y; yy < quad_y + 3 && found == 0; yy++ {
			for xx = quad_x; xx < quad_x + 3 && found == 0; xx++ {
				if SudGrid[xx][yy] == num {
					found = 1
				}
			}
		}
		if found == 0 {
			break
		}
	}

	return num
}

func PrintGrid() {
	var x, y int

	for y = 0; y < 9; y++ {
		if y % 3 == 0 {
			fmt.Printf("|------|------|------|")
			fmt.Printf("\n")
		}
		for x = 0; x < 9; x++ {
			if x % 3 == 0 {
				fmt.Printf("|")
			}
			if SudGrid[x][y] == 0 {
				fmt.Printf(". ")
				continue
			}
			fmt.Printf("%d ", SudGrid[x][y])
		}
		fmt.Printf("|\n")
	}
	fmt.Printf("|------|------|------|\n")
	fmt.Printf("\n")
}

func MakeSudoku(start_moves int) {
	var x, y int

	var attempts int
	attempts = 0
	for {
		attempts++
		if attempts > 5000 {
			// failed, clean this up later so it never happens
			fmt.Printf("Failed to make puzzle\n")
			return
		}
		var done int
		done = 1
		clegacy.MemSet(unsafe.Pointer(&SudGrid), 0, unsafe.Sizeof(SudGrid))
		for y = 0; y < 9 && done == 1; y++ {
			for x = 0; x < 9 && done == 1; x++ {
				SudGrid[x][y] = FindFreeNum(x, y)
				if SudGrid[x][y] < 0 {
					done = 0
				}
			}
		}
		if done == 1 {
			break
		}
	}

	// solution
	PrintGrid()

	// puzzle
	var start int
	start = 9 * 9 - start_moves
	for start > 0 {
		for y = 0; y < 9 && start > 0; y++ {
			for x = 0; x < 9 && start > 0; x++ {
				if SudGrid[x][y] == 0 {
					continue
				}
				if rand.Intn(5) == 0 {
					SudGrid[x][y] = 0
					start--
				}
			}
		}
	}
	PrintGrid()

	// debug
	// fmt.Printf("%d tries\n", attempts);
}

func main() {
	// init the random seed
	rand.Seed(time.Now().UnixNano())
	// generate the puzzle
	MakeSudoku(20)
}
