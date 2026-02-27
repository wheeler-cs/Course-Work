#ifndef _PROBLEMG1_H
#define _PROBLEMG1_H

#define WORLD_WIDTH 10
#define WORLD_HEIGHT 10

// P * Q = Num of processes
#define P 2
#define Q 4

enum CellState
{
    STATE_DEAD,
    STATE_ALIVE,
};

struct ProcessMap
{
    int rows,
        extraRows,
        cols,
        extraCols;
};

struct ProcessChunkInfo
{
    int rowStart,
        rowEnd,
        rowRange,
        colStart,
        colEnd,
        colRange;
};

struct ProcessMap * initProcMap(int, int);
void deallocProcMap(struct ProcessMap *);
void initProcChunkInfo(struct ProcessChunkInfo *);
struct ProcessChunkInfo calcBoundaries(int, struct ProcessMap *);
int * flattenMap(int [WORLD_WIDTH][WORLD_HEIGHT]);
void calcDisplCounts(int *, int *, struct ProcessMap *);
void initWorld(int [WORLD_WIDTH][WORLD_HEIGHT]);
int isCellAlive(int, int, int [WORLD_WIDTH][WORLD_HEIGHT]);
void blinkerDemo(int [WORLD_WIDTH][WORLD_HEIGHT]);
void beaconDemo(int [WORLD_WIDTH][WORLD_HEIGHT]);
void gliderDemo(int [WORLD_WIDTH][WORLD_HEIGHT]);
void updateWorld(int [WORLD_WIDTH][WORLD_HEIGHT]);
void printWorld(int [WORLD_WIDTH][WORLD_HEIGHT]);


#endif
