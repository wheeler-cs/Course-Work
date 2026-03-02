#ifndef _PROBLEMG1_H
#define _PROBLEMG1_H

#include <stdlib.h>

#define DEBUG

#ifdef DEBUG
#define DBGPRINT(...) \
        printf("\n[DEBUG] "); \
        printf(__VA_ARGS__); \
        fflush(stdout);
#else
// Disable debug printing if undefined
#define DBGPRINT(...)
#endif

#define WORLD_WIDTH 21
#define WORLD_HEIGHT 10

// P * Q = Num of processes
#define P 2
#define Q 4

#define ITERATIONS 10

enum ReceiveTag
{
    TAG_NORTH,
    TAG_SOUTH,
    TAG_EAST,
    TAG_WEST,
    TAG_NORTHEAST,
    TAG_NORTHWEST,
    TAG_SOUTHEAST,
    TAG_SOUTHWEST,
};

enum WorldUpdateTag
{
    TAG_SUBWORLD_HEIGHT,
    TAG_SUBWORLD_WIDTH,
    TAG_SUBWORLD_ROW_ORIGIN,
    TAG_SUBWORLD_COL_ORIGIN,
    TAG_SUBWORLD_DATA,
};

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
void exchangeHalos(int **, struct ChunkHalos *, struct NeighborRanks *);

void updateSubWorld(int **, struct ChunkHalos *, struct ProcessChunkInfo *);
int isCellAlive(int, int, int **);

void blinkerDemo(int **);
void gliderDemo(int **);
void printSubworld(int **, struct ProcessChunkInfo *);

void aggregateSubWorlds(int [WORLD_HEIGHT][WORLD_WIDTH], struct ProcessMap *);
void forwardSubWorld(int **, struct ProcessChunkInfo *);
void applySubWorld(int [WORLD_HEIGHT][WORLD_WIDTH], int **, struct ProcessChunkInfo *);

// Code for Game of Life logic
void initWorld(int [WORLD_HEIGHT][WORLD_WIDTH]);
void beaconDemo(int [WORLD_WIDTH][WORLD_HEIGHT]);
void printWorld(int [WORLD_HEIGHT][WORLD_WIDTH]);


#endif
