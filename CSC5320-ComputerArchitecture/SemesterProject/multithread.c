#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define A_ROWS 1000
#define A_COLS 1000
#define B_ROWS A_COLS
#define B_COLS 500

// Matrices used as part of the multiplication operation
int matrix_a[A_ROWS][A_COLS],
    matrix_b[B_ROWS][B_COLS];
    
volatile int matrix_r[A_ROWS][B_COLS];

void init_matrix_a();
void init_matrix_b();
void mult_matrix_instance(unsigned int *);

int main(int argc, char** argv)
{
    // Blank init results matrix
    for(unsigned int i = 0; i < A_ROWS; i++)
    {
        for(unsigned int j = 0; j < B_COLS; j++)
        {
            matrix_r[i][j] = 0;
        }
    }

    // Initialize the input matrices
    pthread_t m_a, m_b;
    pthread_create(&m_a, NULL, (void *)(&init_matrix_a), NULL);
    pthread_create(&m_b, NULL, (void *)(&init_matrix_b), NULL);
    pthread_join(m_a, NULL);
    pthread_join(m_b, NULL);

    // Multiply two matrices
    pthread_t* thread_array[A_ROWS];
    unsigned int * i_ptr;
    for(unsigned int i = 0; i < A_ROWS; i++)
    {
        thread_array[i] = (pthread_t *)malloc(sizeof(pthread_t));
        i_ptr = (unsigned int *)malloc(sizeof(unsigned int));
        *i_ptr = i;
        pthread_create(thread_array[i], NULL, (void *)(&mult_matrix_instance), (void *)i_ptr);
    }
    // Wait for threads to join and deallocate them
    for(unsigned int i = 0; i < A_ROWS; i++)
        pthread_join(*thread_array[i], NULL);
    for(unsigned int i = 0; i < A_ROWS; i++)
        free(thread_array[i]);

    return 0;
}

void init_matrix_a()
{
    // Init matrix A
    for(unsigned int i = 0; i < A_ROWS; i++)
    {
        for(unsigned int j = 0; j < A_COLS; j++)
        {
            matrix_a[i][j] = (i+j);
        }
    }
}

void init_matrix_b()
{
    // Init matrix B
    for(unsigned int i = 0; i < B_ROWS; i++)
    {
        for(unsigned int j = 0; j < B_COLS; j++)
        {
            matrix_b[i][j] = (i+j);
        }
    }
}

void mult_matrix_instance(unsigned int * i)
{
    for(unsigned int j = 0; j < B_COLS; j++)
    {
        for(unsigned int k = 0; k < B_ROWS; k++)
        {
            matrix_r[*i][j] += matrix_a[*i][k] * matrix_b[k][j];
        }
    }
    free(i); // Free the iterator
}
