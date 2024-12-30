#ifndef GHOSTAI_H
#define GHOSTAI_H
#include <math.h>
#include "../GLCD/GLCD.h" 

int moveGhost(int *prex, int *prey, int width, int height, const int* walltiles, 
         volatile char map[height][width], int mode, int playerX, int playerY);

int aStar(int startX, int startY, int targetX, int targetY, int width, int height, const int* walltiles, int* nextX, int* nextY);

int heuristic(int x1, int y1, int x2, int y2);

int isValid(int x, int y, int width, int height, const int* walltiles);


typedef struct {
    int status;
    int x, y;
    int prevx, prevy;
	int remainingtime;

} GhostInfo;

#endif

