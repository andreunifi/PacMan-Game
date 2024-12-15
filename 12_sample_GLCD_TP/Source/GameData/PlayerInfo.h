#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H

#include "GLCD/GLCD.h" 

int move(int *prex, int *prey, int dir, int width, int height, const int* walltiles, volatile char map[width][height]);
int move2(int *prex, int *prey, int dir, int width, int height);


typedef struct {
    int lives;
    int x, y;
    int prevx, prevy;
    int score;
} PlayerInfo;


#endif // PLAYER_INFO_H