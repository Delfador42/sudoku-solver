#include "sudoku.h"

int checkRows(Square*** sudoku, Box** boxes)
{
    printf("We got here!\n");
    int i, j, k;
    // Sum is the amount of times that particular value fits a square in that
    // row, if a 3 fits an empty square twice in a row on the second time sum
    // will equal 2 
    int sum[9];

    // Store where we found the solvable element
    int place[9];

    // loop through all the rows
    for (i = 0; i < 9; i++)
    {
        // Initialize sum[] and place[] array to zero
        for ( j = 0; j < 9; j++ ) 
        {
            place[j] = 0;
            sum[j] = 0;
        }

        // loop through each square in the row
        for (j = 0; j < 9; j++)
        {
            // skip squares with values
            if (sudoku[i][j]->number != 0)
            {
                continue;
            }
            // loop through all possibles
            // loop through 1-9 possible values that can go in the square
            for (k = 0; k < 9; k++)
            {
                // possible[k] is a possible value
                if (sudoku[i][j]->possible[k] == 0)
                {
                    // sum[k] is a square in the row
                    sum[k]++;
                    // j is the index for the square we are on
                    place[k] = j;
                }
            }
        }

        // After each row check if any squares can be solved
        for (k = 0; k < 9; k++)
        {
            // if sum == 1 then we've found a solvable square
            if(sum[k] == 1)
            {
                // place[k] is the index for the square in the row
                sudoku[i][place[k]]->number = k + 1;
                sudoku[i][place[k]]->solvable = 0;
                printf("called\n");
                UNSOLVED--;

                updateSudoku(sudoku, i, place[k]);
                updateBoxes(sudoku, i, place[k]);

                return 1;
            }

        }
    }

    return 0;

}
