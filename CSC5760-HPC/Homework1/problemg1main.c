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
    // MPI Initialization
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Map processes to world
    int i, j;
    struct ProcessMap * pMap;
    pMap = initProcMap();
    #ifdef DEBUG
    for(i = 0; i < P; i++)
    {
        printf("\n");
        for(j = 0; j < Q; j++)
        {
            printf("%d ", pMap->map[i][j]);
        }
    }
    #endif

    // Map process neighbors
    struct NeighborRanks * neighbors;
    neighbors = calcNeighbors(rank, pMap);
    #ifdef DEBUG
    printf("\n\n[Neighbors of %d]", rank);
    printf("\n%d %d %d", neighbors->nw, neighbors->n, neighbors->ne);
    printf("\n%d %d %d", neighbors->w, rank, neighbors->e);
    printf("\n%d %d %d", neighbors->sw, neighbors->s, neighbors->se);
    #endif


    /*
    // Setup world for testing
    int world[WORLD_WIDTH][WORLD_HEIGHT];
    initWorld(world);
    gliderDemo(world);

    struct Allocations * allocMap;
    allocMap = initAllocationMap(P, Q);
    #ifdef DEBUG
    printf("[Allocation Map]\nRows: %d\nExtra Rows: %d\nCols: %d\nExtra Cols: %d",
            allocMap->rows, allocMap->extraRows, allocMap->cols, allocMap->extraCols);
    #endif

    // Init MPI
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    */
    // Cleanup
    free(pMap);
    free(neighbors);
    MPI_Finalize();
    printf("\n");

    return 0;
}
