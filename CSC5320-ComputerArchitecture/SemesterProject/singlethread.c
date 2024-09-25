#include <stdio.h>

#define A_ROWS 1000
#define A_COLS 1000
#define B_ROWS A_COLS
#define B_COLS 500

int main(int argc, char** argv)
{
    // Matrices used as part of the multiplication operation
    int matrix_a[A_ROWS][A_COLS],
        matrix_b[B_ROWS][B_COLS],
        matrix_r[A_ROWS][B_COLS];

    // Blank init results matrix
    for(unsigned int i = 0; i < A_ROWS; i++)
    {
        for(unsigned int j = 0; j < B_COLS; j++)
        {
            matrix_r[i][j] = 0;
        }
    }

    // Init matrix A
    for(unsigned int i = 0; i < A_ROWS; i++)
    {
        for(unsigned int j = 0; j < A_COLS; j++)
        {
            matrix_a[i][j] = (i+j);
        }
    }

    // Init matrix B
    for(unsigned int i = 0; i < B_ROWS; i++)
    {
        for(unsigned int j = 0; j < B_COLS; j++)
        {
            matrix_b[i][j] = (i-j);
        }
    }

    // Multiply [A] * [B]
    for(unsigned int i = 0; i < A_ROWS; i++)
    {
        for(unsigned int j = 0; j < B_COLS; j++)
        {
            for(unsigned int k = 0; k < B_ROWS; k++)
            {
                matrix_r[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }

    return 0;
}
