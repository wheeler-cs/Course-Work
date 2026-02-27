#include "problemg1.h"

#include <stdio.h>
#include <stdlib.h>

struct ProcessMap * initProcMap(int p, int q)
{
    // Allocate memory
    struct ProcessMap * pMap;
    pMap = malloc(sizeof(struct ProcessMap));

    // Calculate sizes
    pMap->rows      = WORLD_HEIGHT / P;
    pMap->extraRows = WORLD_HEIGHT % P;
    pMap->cols      = WORLD_WIDTH  / Q;
    pMap->extraCols = WORLD_WIDTH  % Q; 
}

void deallocProcMap(struct ProcessMap * pMap)
{
    free(pMap);
    pMap = NULL;
}

void initProcChunkInfo(struct ProcessChunkInfo * pChunkInfo)
{
    pChunkInfo->rowStart = 0;
    pChunkInfo->rowEnd = 0;
    pChunkInfo->rowRange = 0;
    pChunkInfo->colStart = 0;
    pChunkInfo->colEnd = 0;
    pChunkInfo->colRange = 0;
}

struct ProcessChunkInfo calcBoundaries(int rank, struct ProcessMap * pMap)
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

int * flattenMap(int world[WORLD_WIDTH][WORLD_HEIGHT])
{
    int * flatWorld, i, j;
    flatWorld = malloc(sizeof(int) * WORLD_HEIGHT * WORLD_WIDTH);
    // Convert 2-D world into 1-D array
    for(i = 0; i < WORLD_HEIGHT; i++)
    {
        for(j = 0; j < WORLD_WIDTH; j++)
        {
            flatWorld[i * WORLD_WIDTH + j] = world[i][j];
        }
    }

    return flatWorld;
}

void calcDisplCounts(int * sendCounts, int * displacements, struct ProcessMap * pMap)
{
    int i,
        localRow, localCol,
        globalRow, globalCol;

    sendCounts = malloc(sizeof(int) * P * Q);
    displacements = malloc(sizeof(int) * P * Q);

    for(int i = 0; i < P * Q; i++) {
        globalRow = i / Q;
        globalCol = i % Q;

        localRow = pMap->rows;
        if(globalRow < pMap->extraRows)
        {
            localRow += 1;
        };
        localCol = pMap->cols;
        if(globalCol < pMap->extraCols)
        {
            localCol += 1;
        }

        sendCounts[i] = localRow * localCol;

        int rowStart = globalRow * pMap->rows;
        if(globalRow < pMap->extraRows)
        {
            rowStart += globalRow;
        }
        else
        {
            rowStart += pMap->extraRows;
        }
        int colStart = globalCol * pMap->cols + (globalCol < pMap->extraCols ? globalCol : pMap->extraCols);

        displacements[i] = rowStart * pMap->cols + colStart;
    }
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
