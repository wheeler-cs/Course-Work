#include "problemg1.h"

#include <stdio.h>
#include <stdlib.h>

struct Allocations * initAllocationMap()
{
    // Allocate memory
    struct Allocations * allocMap;
    allocMap = malloc(sizeof(struct Allocations));

    // Calculate sizes
    allocMap->rows      = WORLD_HEIGHT / P;
    allocMap->extraRows = WORLD_HEIGHT % P;
    allocMap->cols      = WORLD_WIDTH  / Q;
    allocMap->extraCols = WORLD_WIDTH  % Q; 

    return allocMap;
}

void deallocAllocationMap(struct Allocations * allocMap)
{
    free(allocMap);
    allocMap = NULL;
}

struct ProcessMap * initProcMap()
{
    struct ProcessMap * pMap;
    pMap = malloc(sizeof(struct ProcessMap));

    int i, j;
    for(i = 0; i < P; i++)
    {
        for(j = 0; j < Q; j++)
        {
            pMap->map[i][j] = (i * Q) + j;
        }
    }

    return pMap;
}

struct NeighborRanks * calcNeighbors(int rank, struct ProcessMap * pMap)
{
    int i, j, selfi, selfj;
    struct NeighborRanks * neighbors;

    // Find rank's position in process map
    for(i = 0; i < P; i++)
    {
        for(j = 0; j < Q; j++)
        {
            if(pMap->map[i][j] == rank)
            {
                selfi = i;
                selfj = j;
                i = P;
                break;
            }
        }
    }

    // Find neighboring processes (clockwise order from top left corner)
    neighbors = malloc(sizeof(struct NeighborRanks));
    neighbors->nw = pMap->map[((selfi + P) - 1) % P][((selfj + Q) - 1) % Q];
    neighbors->n  = pMap->map[((selfi + P) - 1) % P][selfj];
    neighbors->ne = pMap->map[((selfi + P) - 1) % P][(selfj + 1) % Q];
    neighbors->e  = pMap->map[selfi][(selfj + 1) % Q];
    neighbors->se = pMap->map[(selfi + 1) % P][(selfj + 1) % Q];
    neighbors->s  = pMap->map[(selfi + 1) % P][selfj];
    neighbors->sw = pMap->map[(selfi + 1) % P][((selfj + Q) - 1) % Q];
    neighbors->w  = pMap->map[selfi][((selfj + Q) - 1) % Q];

    return neighbors;
}

struct ProcessChunkInfo calcBoundaries(int rank, struct Allocations * pMap)
{
    struct ProcessChunkInfo pChunkInfo;
    int procMapRow, procMapCol;
    procMapRow = rank / Q;
    procMapCol = rank % Q;

    // Calculate row and column range
    pChunkInfo.rowRange = pMap->rows;
    if(procMapRow < pMap->extraRows)
    {
        pChunkInfo.rowRange += 1;
    }
    pChunkInfo.colRange = pMap->cols;
    if(procMapCol < pMap->extraCols)
    {
        pChunkInfo.colRange += 1;
    }
    // Calculate row start
    pChunkInfo.rowStart = procMapRow * pMap->rows;
    if(procMapRow < pMap->extraRows)
    {
        pChunkInfo.rowStart += procMapRow;
    }
    else
    {
        pChunkInfo.rowStart += pMap->extraRows;
    }
    // Calculate column start
    pChunkInfo.colStart = procMapCol * pMap->cols;
    if(procMapCol < pMap->extraCols)
    {
        pChunkInfo.colStart += procMapCol;
    }
    else
    {
        pChunkInfo.colStart += pMap->extraCols;
    }
    // Calculate row and column end
    pChunkInfo.rowEnd = (pChunkInfo.rowStart + pChunkInfo.rowRange) % WORLD_HEIGHT;
    pChunkInfo.colEnd = (pChunkInfo.colStart + pChunkInfo.colRange) % WORLD_WIDTH;

    return pChunkInfo;
}

struct ChunkHalos * initHalos(int rowRange, int colRange)
{
    struct ChunkHalos * halos;
    halos = malloc(sizeof(struct ChunkHalos));

    // Set sizes of halos
    halos->eHaloSize = rowRange;
    halos->wHaloSize = rowRange;
    halos->nHaloSize = colRange;
    halos->sHaloSize = colRange;

    // Allocation memroy for halos
    halos->eHalo  = malloc(sizeof(int) * halos->eHaloSize);
    halos->wHalo  = malloc(sizeof(int) * halos->wHaloSize);
    halos->nHalo  = malloc(sizeof(int) * halos->nHaloSize);
    halos->sHalo  = malloc(sizeof(int) * halos->sHaloSize);
    halos->neHalo = malloc(sizeof(int));
    halos->nwHalo = malloc(sizeof(int));
    halos->seHalo = malloc(sizeof(int));
    halos->swHalo = malloc(sizeof(int));

    return halos;
}

void deallocHalos(struct ChunkHalos * halos)
{
    free(halos->nHalo);
    free(halos->sHalo);
    free(halos->eHalo);
    free(halos->wHalo);
    free(halos->neHalo);
    free(halos->nwHalo);
    free(halos->seHalo);
    free(halos->swHalo);
    free(halos);
    halos = NULL;
}


void initWorld(int world[WORLD_WIDTH][WORLD_HEIGHT])
{
    int i, j;
    for(i = 0; i < WORLD_WIDTH; i++)
    {
        for(j = 0; j < WORLD_HEIGHT; j++)
        {
            world[i][j] = STATE_DEAD;
        }
    }
}

int isCellAlive(int x, int y, int world[WORLD_WIDTH][WORLD_HEIGHT])
{
    int neighbors, i, j, xOffset, yOffset;
    neighbors = 0;
    // Check 3 x 3 box around 
    for(i = -1; i <= 1; i++)
    {
        for(j = -1; j <= 1; j++)
        {
            // Skip over self
            if((i == 0) && (j == 0))
            {
                continue;
            }
            // Check cell state, being mindful of wrapping
            xOffset = ((x + WORLD_WIDTH) + i) % WORLD_WIDTH;
            yOffset = ((y + WORLD_HEIGHT) + j) % WORLD_HEIGHT;
            if(world[xOffset][yOffset] == STATE_ALIVE)
            {
                neighbors++;
            }
        }
    }
    if(world[x][y] == STATE_ALIVE)
    {
        // If alive @ t, is alive @ t + 1 if has 2 or 3 neighbors
        if(neighbors != 2 && neighbors != 3)
        {
            return STATE_DEAD;
        }
        else
        {
            return STATE_ALIVE;
        }
    }
    else
    {
        // If dead @ t, is alive @ t + 1 if has 3 neighbors
        if(neighbors == 3)
        {
            return STATE_ALIVE;
        }
        else
        {
            return STATE_DEAD;
        }
    }
}

void blinkerDemo(int world[WORLD_WIDTH][WORLD_HEIGHT])
{
    world[0][0] = STATE_ALIVE;
    world[0][1] = STATE_ALIVE;
    world[0][2] = STATE_ALIVE;
}

void beaconDemo(int world[WORLD_WIDTH][WORLD_HEIGHT])
{
    world[0][0] = STATE_ALIVE;
    world[0][1] = STATE_ALIVE;
    world[1][0] = STATE_ALIVE;
    world[2][3] = STATE_ALIVE;
    world[3][3] = STATE_ALIVE;
    world[3][2] = STATE_ALIVE;
}

void gliderDemo(int world[WORLD_WIDTH][WORLD_HEIGHT])
{
    world[2][2] = STATE_ALIVE;
    world[3][2] = STATE_ALIVE;
    world[4][2] = STATE_ALIVE;
    world[4][3] = STATE_ALIVE;
    world[3][4] = STATE_ALIVE;
}

void updateWorld(int world[WORLD_WIDTH][WORLD_HEIGHT])
{
    int i, j;
    int worldCopy[WORLD_WIDTH][WORLD_HEIGHT];
    // Check cell states
    for(i = 0; i < WORLD_WIDTH; i++)
    {
        for(j = 0; j < WORLD_HEIGHT; j++)
        {
            // Save cell state to a world copy
            worldCopy[i][j] = isCellAlive(i, j, world);
        }
    }
    // Transfer from copy to actual world
    for(i = 0; i < WORLD_WIDTH; i++)
    {
        for(j = 0; j < WORLD_HEIGHT; j++)
        {
            world[i][j] = worldCopy[i][j];
        }
    }
}

void printWorld(int world[WORLD_WIDTH][WORLD_HEIGHT])
{
    int i, j;
    printf("\n");
    for(j = WORLD_HEIGHT - 1; j >= 0; j--)
    {
        for(i = 0; i < WORLD_WIDTH; i++)
        {
            if(world[i][j] == STATE_ALIVE)
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}
