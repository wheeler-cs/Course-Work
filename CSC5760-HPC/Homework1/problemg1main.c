// Main header
#include "problemg1.h"

// Terminal utilities (for prettier printing)
#include "Terminal.h"

// Library includes
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Needed for sleep()

int main(int argc, char ** argv)
{
    // Setup world for testing
    int world[WORLD_WIDTH][WORLD_HEIGHT];
    initWorld(world);
    gliderDemo(world);

    // Calculate subprocess division boundaries
    struct ProcessMap * pMap;
    pMap = initProcMap(P, Q);

    // Init MPI
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    struct ProcessChunkInfo pChunkInfo;
    pChunkInfo = calcBoundaries(rank, pMap);

    int * flatWorld = flattenMap(world);


    int * sendCounts,
        * displacements;

    calcDisplCounts(sendCounts, displacements, pMap);
    int localSize = pChunkInfo.rowRange * pChunkInfo.colRange;
    int* localGrid = malloc(sizeof(int) * localSize);

    MPI_Scatterv(flatWorld,       // send buffer (root only)
                 sendCounts,     // elements to send to each process
                 displacements,         // displacement for each process
                 MPI_INT,        // datatype
                 localGrid,      // receive buffer
                 localSize,      // number of elements to receive
                 MPI_INT,
                 0,
                 MPI_COMM_WORLD);


    // Cleanup
    MPI_Finalize();
    printf("\n");
    return 0;
}
