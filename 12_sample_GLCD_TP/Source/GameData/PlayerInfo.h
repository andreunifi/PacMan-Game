#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H

#include "GLCD/GLCD.h" 
#include <stdio.h> /*for sprintf*/
#include "LPC17xx.h"
#include "timer.h"

#include "GameData/GhostAI.h"
int move(int *prex, int *prey, int dir, int width, int height, const int* walltiles, volatile char map[width][height]);



#define MAP_WIDTH 30    // 240 pixels / 8px per character
#define MAP_HEIGHT 30
extern int score;



extern int cointiles[MAP_HEIGHT*MAP_WIDTH];
extern int poweruptiles[MAP_HEIGHT*MAP_WIDTH];
extern int teleportlocation[MAP_HEIGHT*MAP_WIDTH];

typedef struct {
    int lives;
    int x, y;
    int prevx, prevy;

} PlayerInfo;


#endif // PLAYER_INFO_H