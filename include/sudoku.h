#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <stdlib.h>

// This is nine one's in binary ie 111111111
// If the cell has a number already then it's code should be this

// We are saying that POSSIBLE is going to be defined, but we are not defining
// it here
extern int UNSOLVED;
extern int SIZE_ROWS;
extern int SIZE_COLUMNS;

typedef struct Sudoku {
    struct Square*** squares;
    struct Box** boxes;
} Sudoku;

// Each box contains 9 squares
typedef struct Box 
{
    // An array of Squares
    struct Square** squares;
    int numbers;
    int possible[9];
    int solvable;
    struct Box* next;

} Box;

// We are going to represent each of the squares, (ie cell in a square) with
// a datatype called Square
typedef struct Square
{
    int number;

    // We'll go to index four and say does four fit into the square, if it has
    // a 0 it can and 1 if not
    // 0 means that it is possible to solve, but we don't know what number
    // goes there
    // 1 means that it is not solveable
    // Array initialized to all zeros
    /* [0] [0] [0] [0] [0] [0] [0] [0] [0] // Initialized array 1 no  0 yes
     * [8] [7] [6] [5] [4] [3] [2] [1] [0] // index
     * [9] [8] [7] [6] [5] [4] [3] [2] [1] // Possible Square Values
     */
    int possible[9];
    int solvable;

    // Tell us what box the square is in
    Box* box;

    int row;
    int column;
} Square;


int** createPuzzle();
void printPuzzle(Square*** puzzle);
Sudoku* setUpPuzzle(int** puzzle);
Sudoku* createSudoku(Square*** puzzle, Box** boxes);
int updateSudoku(Square*** sudoku, int row, int column);
int checkPuzzle(Square*** sudoku, Box** boxes);
int solveSquare(Square* square);

/* box functions */
Box** createBoxes();
int updateBoxes(Square*** sudoku, int row, int column);
int boxSingles(Square*** sudoku, Box** boxes);
int checkRows(Square*** sudoku, Box** boxes);

#endif // SUDOKU_H

