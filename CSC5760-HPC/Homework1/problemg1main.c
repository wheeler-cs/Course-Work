// Main header
#include "problemg1.h"

// Terminal utilities (for prettier printing)
#include "Terminal.h"

// Library includes
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Needed for sleep()

/* I'm not normally one for griping about an assignment, but I think something
 * needs to be said about this one. I think the difficulty of this homework
 * does not accurately reflect the fact that it is the first one of the
 * semester; that is, I believe that it was inappropriate for the level of
 * knowledge we currently have. Regardless of the fact that this is for the
 * graduate-level section of this course, just about everyone in this class is
 * still new to the concepts of parallel computing, and MPI is still a brand
 * new library to us. Me, personally, I've had very limited experience with
 * pthreads, and that's the extent of my knowledge about parallel computing.
 * 
 * I genuinely put my best effort into writing this program, but I've had course
 * semester projects with fewer lines of source code than what I've put in here.
 * I just wish there had been a more gradual introduction to MPI, and that the
 * lectures had gone into more detail about what each function does and how it
 * works.Some smaller code examples that we could pull from would also have been
 * helpful. While the examples provided do have valuable information, they are
 * monolithic and pretty intimidating to break down.
 * 
 * Again, I'm typically not the person who complains about an assignment, but
 * I think this was excessive for the first one of the semester.
 */

int main(int argc, char ** argv)
{
    int world[WORLD_WIDTH][WORLD_HEIGHT];
    gliderDemo(world);

    // MPI Initialization
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Calculate how many extra rows and columns there are
    struct Allocations * allocMap;
    allocMap = initAllocationMap();
    #ifdef DEBUG
    printf("\nRows: %d, Extra: %d\nCols: %d, Extra: %d\n",
           allocMap->rows, allocMap->extraRows, allocMap->cols, allocMap->extraCols);
    #endif
    
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

    // Calculate sub-world chunk sizes and allocate
    struct ProcessChunkInfo pcInfo;
    int ** subWorld;
    pcInfo = calcBoundaries(rank, allocMap);
    #ifdef DEBUG
    printf("\nRank: %d, Row Range: %d, Col Range: %d", rank, pcInfo.rowRange, pcInfo.colRange);
    #endif
    subWorld = malloc(sizeof(int) * pcInfo.rowRange);
    for(i = 0; i < pcInfo.colRange; i++)
    {
        subWorld[i] = malloc(sizeof(int) * pcInfo.colRange);
    }

    // Setup halos for data from other processes
    struct ChunkHalos * halos;
    halos = initHalos(pcInfo.rowRange, pcInfo.colRange);

    // Run game for n iterations
    for(i = 0; i < ITERATIONS; i++)
    {
        exchangeHalos(subWorld, halos, neighbors);

        // Update world if rank 0
        if(rank == 0)
        {
            world[0][0] = 1;
            printWorld(world);
        }
        sleep(0.5);
    }

    // Cleanup
    deallocAllocationMap(allocMap);
    deallocHalos(halos);
    free(pMap);
    free(neighbors);
    MPI_Finalize();
    printf("\n");

    return 0;
}
