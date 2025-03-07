#include "GameData/GhostAI.h"
extern GhostInfo blinkly;
#include<stdlib.h>

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2); // Manhattan distance
}



int isValid(int x, int y, int width, int height, const int* walltiles) {
    if (x < 0 || x >= width || y < 0 || y >= height) return 0;
    return walltiles[y * width + x] == 0; // Assuming walltiles == 0 is walkable
}

int moveGhost(int *prex, int *prey, int width, int height, const int* walltiles, 
         volatile char map[height][width], int mode, int playerX, int playerY) {

    if (mode == 1) { // Chasing mode
        int nextX, nextY;
        aStar(*prex, *prey, playerX, playerY, width, height, walltiles, &nextX, &nextY);
				
				
				
			  if(cointiles[(*prey)*MAP_WIDTH + (*prex)] == 1){
					
					map[*prey][*prex]='*';
					drawNormalPill(*prex,*prey);
					//PutChar(*prex*8,*prey*16,'*',Yellow,Black);
				}else if(poweruptiles[(*prey)*MAP_WIDTH + (*prex)] == 1){
					
				map[*prey][*prex]='X';
				drawBigPill(*prex,*prey);	
				//PutChar(*prex*8,*prey*16,'X',Red,Black);
				}else {
				map[*prey][*prex]=' ';
				emptytile(*prex,*prey);	
				//PutChar(*prex*8,*prey*16,' ',Black,Black);
				}
					
				
    // Update position
				blinkly.prevx=*prex;
				blinkly.prevy=*prey;
				*prex=nextX;
				*prey=nextY;
				
				map[nextY][nextX]='0';
				drawGhost(nextX,nextY);
				//PutChar(nextX*8,nextY*16,'O',Red,Black);
        blinkly.x=nextX;
				blinkly.y=nextY;
        return 1; // Move successful
    }

    if (mode == 2) { // Scared mode (does nothing for now)
			  int nextX, nextY;
				//this goes in the opposite direction than player
        aStar(*prex, *prey, blinkly.x + (blinkly.x - playerX), blinkly.y + (blinkly.y - playerY), width, height, walltiles, &nextX, &nextY);
				
			
			if(cointiles[(*prey)*MAP_WIDTH + (*prex)] == 1){
					
					map[*prey][*prex]='*';
					drawNormalPill(*prex,*prey);
					//PutChar(*prex*8,*prey*16,'*',Yellow,Black);
				}else if(poweruptiles[(*prey)*MAP_WIDTH + (*prex)] == 1){
					
				map[*prey][*prex]='X';
				drawBigPill(*prex,*prey);
				//PutChar(*prex*8,*prey*16,'X',Red,Black);
				}else {
				map[*prey][*prex]=' ';
					emptytile(*prex,*prey);	
				//PutChar(*prex*8,*prey*16,' ',Black,Black);
				}
					
				
    // Update position
				blinkly.prevx=*prex;
				blinkly.prevy=*prey;
				*prex=nextX;
				*prey=nextY;
				
				map[nextY][nextX]='0';
				drawGhostScared(nextX,nextY); //modified blinkly
				//PutChar(nextX*8,nextY*16,'O',Blue,Black);
        blinkly.x=nextX;
				blinkly.y=nextY;
        return 0; // Move successful
    }
			
			
			

    return -1; // Invalid mode
}
				 
int aStar(int startX, int startY, int targetX, int targetY, int width, int height, const int* walltiles, int* nextX, int* nextY) {
      int bestX = startX, bestY = startY;
			int bestScore = heuristic(startX, startY, targetX, targetY);

    const int dx[] = {0, 1, 0, -1}; // Right, Down, Left, Up
    const int dy[] = {-1, 0, 1, 0};

    for (int i = 0; i < 4; ++i) {
        int nx = startX + dx[i];
        int ny = startY + dy[i];

        if (isValid(nx, ny, width, height, walltiles)) {
            int score = heuristic(nx, ny, targetX, targetY);
            if (score < bestScore) {
                bestScore = score;
                bestX = nx;
                bestY = ny;
            }
        }
    }

    if (bestX == startX && bestY == startY) {
        return 0; // No valid moves
    }

    *nextX = bestX;
    *nextY = bestY;
    return 1;
}