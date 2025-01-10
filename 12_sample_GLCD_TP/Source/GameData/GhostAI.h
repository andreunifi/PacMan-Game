#ifndef GHOSTAI_H
#define GHOSTAI_H
#include <math.h>
#include "../GLCD/GLCD.h" 

#define MAP_WIDTH 30    // 240 pixels / 8px per character
#define MAP_HEIGHT 18

int moveGhost(int *prex, int *prey, int width, int height, const int* walltiles, 
         volatile char map[height][width], int mode, int playerX, int playerY);

int aStar(int startX, int startY, int targetX, int targetY, int width, int height, const int* walltiles, int* nextX, int* nextY);

int heuristic(int x1, int y1, int x2, int y2);

int isValid(int x, int y, int width, int height, const int* walltiles);

extern int cointiles[MAP_HEIGHT*MAP_WIDTH];
extern int poweruptiles[MAP_HEIGHT*MAP_WIDTH];

typedef struct {
    int status;
    int x, y;
    int prevx, prevy;
		int remainingtime;
		int respawntime;

} GhostInfo;

#endif

