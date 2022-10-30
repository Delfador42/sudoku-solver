#include "sudoku.h"

Sudoku* createSudoku(Square*** squares, Box** boxes)
{
    Sudoku* sudoku;
    sudoku = malloc(sizeof(Sudoku));

    sudoku->squares = squares;
    sudoku->boxes = boxes;

    return sudoku;
}

// Initialize a type
Sudoku* setUpPuzzle(int** puzzle)
{
    Square*** sudoku;
    Box** boxes;
    int i, j, x;
    // We start in the 0 box, this is for tracking what box we are adding to
    int currentBox = 0;

    // Dynamically allocate sudoku
    sudoku = (Square***)malloc(sizeof(Square**)*9);

    // Creates an array of boxes
    boxes = createBoxes();

    // Loop through rows
    for (i = 0; i < SIZE_ROWS; i++)
    {
        // Allocate space for each array
        sudoku[i] = (Square**)malloc(sizeof(Square*)*9);

        // Loop through columns
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            // Allocate memory for each individual cell
            // Initialize the element at sudoku[i][j] to be of type 
            // "pointer to Square"
        
            /*
             * Ref: https://www.cs.toronto.edu/~heap/270F02/node31.html
             *
             * As we can see
             * ...
             * n1 = (struct node *) malloc(sizeof(struct node));
               n2 = (struct node *) malloc(sizeof(struct node));
               n3 = (struct node *) malloc(sizeof(struct node));
               ...
             * You are creating a new instance of the struct with each malloc
             * In the mallocs above, are they returning the same address?
             * No, You are creating a new instance of the struct and returning
             * a pointer to it. This is the same thing that is happening below,
             * the element at sudoku[i][j] is a pointer of type "pointer to
             * Square" to its own instance of the Square struct.
             *
             */

            sudoku[i][j] = (Square*)malloc(sizeof(Square)*9);

            // puzzle is a 2d array
            //
            sudoku[i][j]->number = puzzle[i][j];

            // Every element of sudoku is a struct of type Square (a cell)
            sudoku[i][j]->row = i;
            sudoku[i][j]->column = j;
            sudoku[i][j]->solvable = 9;

            // Keep track of what box we are in there are 9 boxes in sudoku we
            // start in the 0 box, we need to keep track of what square we are
            // at to know what box we are in, the first 3 squares are in box 0,
            // the next 3 in box 1
            boxes[currentBox]->squares[ boxes[currentBox]->numbers ] = sudoku[i][j];
            // Gives access to the current box
            sudoku[i][j]->box = boxes[currentBox];
            boxes[currentBox]->numbers++;

            // Initialize the possible array to all 0
            // could be SIZE_COLUMNS it doesn't matter
            for (x = 0; x < SIZE_ROWS; x++)
            {
                sudoku[i][j]->possible[x] = 0;
            }

            // after 3 squares you enter the next box there are 3 box per row,
            // 9 boxes in a sudoku game
            if (j == 2)
            {
                currentBox++;
            }
            if (j == 5)
            {
                currentBox++;
            }
            
        }
        // Reset the Box counter, only 3 rows at a time
        currentBox -= 2;
        if (i == 2)
        {
            currentBox = 3;
        }
        if (i == 5)
        {
            currentBox = 6;
        }
    }

    // loop through rows
    for (i = 0; i < SIZE_ROWS; i++)
    {
        // loop through columns
        for (j=0; j < SIZE_COLUMNS; j++)
        {
            /*
             * If you find a 1 in a cell then it tells you that you can't have
             * another 1 in that column or row, so we are going to loop through
             * the entire row and entire column and say that 1 cannot go into
             * any of those squares
             */
            // If its not 0 it has a number
            if (sudoku[i][j]->number != 0)
            {
                // solvable is the number of possible numbers in that square
                sudoku[i][j]->solvable = 0;

                // call function that will loop through rows and columns and
                // update the possible[] and solvable
                updateSudoku(sudoku, i, j);
                // update the possible[] and solvable[] for each box
                updateBoxes(sudoku, i, j);
                UNSOLVED--;
            }

        }
    }

    return createSudoku(sudoku, boxes);

}


// updateSudoku() loops through columns and rows changing solvable and
// possible[] array
// sudoku is a double array of pointers to type Square, thats why the ***
int updateSudoku(Square*** sudoku, int row, int column)
{
    int x, y;
    int number = sudoku[row][column]->number;
    // loop through the column
    // The row is the changing variable so we are looping through the column
    for (x = 0; x < SIZE_ROWS; x++)
    {
        // -1 because it's zero based
        // possible[] elements are 0 or 1 
        // posible is an array we are comparing the elemnt at that index
        if (sudoku[x][column]->possible[number - 1] == 0)
        {
            // solvable is the number of possible numbers in that square
            sudoku[x][column]->solvable--;
        }
        sudoku[x][column]->possible[number -1] = 1;
    } 

    // Loop through the row
    for (y = 0; y < SIZE_COLUMNS; y++)
    {
        // -1 because it's zero based
        // possible[] elements are 0 or 1 
        // posible is an array we are comparing the elemnt at that index
        if (sudoku[row][y]->possible[number - 1] == 0)
        {
            // solvable is the number of possible numbers in that square
            sudoku[row][y]->solvable--;
        }
        sudoku[row][y]->possible[number -1] = 1;
    } 

    return 1;
}


// checking if solvable == 1, means that theres only 1 possible value the
// square could be
int checkPuzzle(Square*** sudoku, Box** boxes)
{
    int i, j, x;

    // Run the rows and columns trick
    for (i = 0; i < SIZE_ROWS; i++)
    {
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            if (sudoku[i][j]->solvable == 1)
            {
                // Note that element sudoku[i][j] is a Square*
                solveSquare(sudoku[i][j]);
                updateSudoku(sudoku, i , j);
                updateBoxes(sudoku, i, j);
                return 1;
            }
        }
    }

    // Run the box trick
    // If we solve something it will return 1 if not return 0
    if (boxSingles(sudoku, boxes))
        return 1;

    return checkRows(sudoku, boxes);
}



int** createPuzzle()
{
    /*
     * int *ptr;   //ptr points to an int
     * char *cptr; //cptr points to a char
     *
     * ptr and cptr are both pointers but their specific type is different
     * ptr's type is "pointer to int", It can point to a memory location that
     * stores an int value
     * cptr's type is "pointer to char" it can point to a memory location that
     * stores a char value
     */
    int **puzzle;
    int i, j;

    // We cant return array yet because it is not dynamically allocated, so we
    // need to return the puzzle
    /*
     * The reason we need can't return the array is because it is created in
     * the funciton and thus would be destroyed on return, this array lives on
     * the stack and we need to copy it to the heap inorder for it to live on
     * after the function ends
     */
    int array[9][9] = {0, 1, 9,     0, 0, 2,    0, 0, 0,
                       4, 7, 0,     6, 9, 0,    0, 0, 1,
                       0, 0, 0,     4, 0, 0,    0, 9, 0,

                       8, 9, 4,     5, 0, 7,    0, 0, 0,
                       0, 0, 0,     0, 0, 0,    0, 0, 0,
                       0, 0, 0,     2, 0, 1,    9, 5, 8,    

                       0, 5, 0,     0, 0, 6,    0, 0, 0,
                       6, 0, 0,     0, 2, 8,    0, 7, 9,    
                       0, 0, 0,     1, 0, 0,    8, 6, 0, };

    // this basically creates 9 arrays
    puzzle = (int**)malloc(sizeof(int*)*9);

    for (i = 0; i < SIZE_ROWS; i++)
    {
        // allocate space for each of those arrays
        puzzle[i] = (int*)malloc(sizeof(int)*9);
        
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            // Copy everything in array to puzzle
            puzzle[i][j] = array[i][j];
        }
    }

//    return array;
    return puzzle;

}


void printPuzzle(Square*** puzzle)
{
    int i, j;
    
    printf("-------------------------------\n");
    for (i = 0; i < SIZE_ROWS; i++)
    {
        printf("|");
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            printf(" %d ",puzzle[i][j]->number);

            if ((j+1) % 3 == 0)
            {
                printf("|");
            }
        }
        printf("\n");
        if ((i+1) % 3 == 0)
        {
            printf("-------------------------------\n");
        }
    }
}
