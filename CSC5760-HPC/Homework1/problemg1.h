#ifndef _PROBLEMG1_H
#define _PROBLEMG1_H

#define WORLD_WIDTH 100
#define WORLD_HEIGHT 100

enum CellState
{
    STATE_DEAD,
    STATE_ALIVE,
};

void initWorld(int [WORLD_WIDTH][WORLD_HEIGHT]);
int isCellAlive(int, int, int [WORLD_WIDTH][WORLD_HEIGHT]);
void blinkerDemo(int [WORLD_WIDTH][WORLD_HEIGHT]);
void beaconDemo(int [WORLD_WIDTH][WORLD_HEIGHT]);
void updateWorld(int [WORLD_WIDTH][WORLD_HEIGHT]);
void printWorld(int [WORLD_WIDTH][WORLD_HEIGHT]);


#endif
