#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <mpi.h>

#define ARRAY_LEN 8

void calculateStartEnd(int rank, int size, int * start, int * end)
{
    int widerStrides, stride;
    // Blank init variables
    *start = 0;
    *end = 0;
    stride = 0;

    // Calculate the number of strides that are wider
    widerStrides = size % rank;

    // Assign starts and ends
    if(rank < widerStrides)
    {
        start = 
    }
    else
    {

    }
}

int main(int argc, char ** argv)
{
    // Variables and init
    int rank,
        size,
        start,
        end,
        addends[ARRAY_LEN],
        array[ARRAY_LEN];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Divide data across threads
    if(rank == 0)
    {
        int i;

        // Init array only for rank 0
        srand(time(NULL));
        for(i = 0; i < ARRAY_LEN; i++)
        {
            addends[i] = rand() % 2;
        }
    }
    MPI_Scatter(addends, ARRAY_LEN, MPI_INT, array, ARRAY_LEN, MPI_INT, 0, MPI_COMM_WORLD);

    calculateStartEnd(rank, size, &start, &end);

    if(rank == 0)
    {
        int i;

        for(i = 0; i < ARRAY_LEN; i++)
        {
            printf("%d %d\n", addends[i], array[i]);
        }
    }

    

    // Clean up
    MPI_Finalize();
    return 0;
}
