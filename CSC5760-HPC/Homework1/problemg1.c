#include "problemg1.h"

#include <stdio.h>
#include <stdlib.h>

struct Allocations * initAllocationMap(int p, int q)
{
    // Allocate memory
    struct Allocations * allocMap;
    allocMap = malloc(sizeof(struct Allocations));

    // Calculate sizes
    allocMap->rows      = WORLD_HEIGHT / p;
    allocMap->extraRows = WORLD_HEIGHT % p;
    allocMap->cols      = WORLD_WIDTH  / q;
    allocMap->extraCols = WORLD_WIDTH  % q; 

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
