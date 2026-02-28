#ifndef _PROBLEMG1_H
#define _PROBLEMG1_H

#define DEBUG

#define WORLD_WIDTH 21
#define WORLD_HEIGHT 10

// P * Q = Num of processes
#define P 2
#define Q 4

#define ITERATIONS 10

enum CellState
{
    STATE_DEAD,
    STATE_ALIVE,
};

struct Allocations
{
    int rows,
        extraRows,
        cols,
        extraCols;
};

struct Allocations * initAllocationMap();
void deallocAllocationMap(struct Allocations *);


struct ProcessMap
{
    int map[P][Q];
};

struct ProcessMap * initProcMap();


struct NeighborRanks
{
    int n, s, e, w, ne, nw, se, sw;
};

struct NeighborRanks * calcNeighbors(int, struct ProcessMap *);


struct ProcessChunkInfo
{
    int rowStart, rowEnd, rowRange,
        colStart, colEnd, colRange;
};

struct ProcessChunkInfo calcBoundaries(int, struct Allocations *);


struct ChunkHalos
{
    int * nHalo,
        * sHalo,
        * eHalo,
        * wHalo,
        * neHalo,
        * nwHalo,
        * seHalo,
        * swHalo;
    int nHaloSize,
        sHaloSize,
        eHaloSize,
        wHaloSize;
};

struct ChunkHalos * initHalos(int, int);
void deallocHalos(struct ChunkHalos *);


// Code for Game of Life logic
void initWorld(int [WORLD_WIDTH][WORLD_HEIGHT]);
int isCellAlive(int, int, int [WORLD_WIDTH][WORLD_HEIGHT]);
void blinkerDemo(int [WORLD_WIDTH][WORLD_HEIGHT]);
void beaconDemo(int [WORLD_WIDTH][WORLD_HEIGHT]);
void gliderDemo(int [WORLD_WIDTH][WORLD_HEIGHT]);
void updateWorld(int [WORLD_WIDTH][WORLD_HEIGHT]);
void printWorld(int [WORLD_WIDTH][WORLD_HEIGHT]);


#endif
