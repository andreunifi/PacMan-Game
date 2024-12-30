#include "GameData/GhostAI.h"

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
				
			
				map[*prey][*prex]=' ';
				PutChar(*prex*8,*prey*16,' ',Black,Black);
    // Update position
				*prex=nextX;
				*prey=nextY;
				
				map[nextY][nextX]='0';
				PutChar(nextX*8,nextY*16,'O',Red,Black);
        
        return 1; // Move successful
    }

    if (mode == 2) { // Scared mode (does nothing for now)
        return 0;
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