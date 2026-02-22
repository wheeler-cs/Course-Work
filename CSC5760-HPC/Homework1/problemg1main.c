#include "problemg1.h"
#include "unistd.h"

#include "Terminal.h"

#include <stdio.h>

int main(int argc, char ** argv)
{
    int world[WORLD_WIDTH][WORLD_HEIGHT];
    initWorld(world);
    beaconDemo(world);
    do
    {
        sleep(1);
        clearScreen();
        setCursorPosition(0, 0);
        printWorld(world);
        updateWorld(world);
    } while(1);
}
