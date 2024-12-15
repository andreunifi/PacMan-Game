
#include "GameData/PlayerInfo.h"


int move2(int* prex, int* prey, int dir, int width, int height) {
	int movx = 0, movy = 0;

    // Determine the movement direction
    switch (dir) {
        case 0: // Up
            movx = 0;
            movy = -1;
            break;
        case 1: // Right
            movx = 1;
            movy = 0;
            break;
        case 2: // Down
            movx = 0;
            movy = 1;
            break;
        case 3: // Left
            movx = -1;
            movy = 0;
            break;
        default:
            return -1; // Invalid direction
    }
		
		int newx = *prex + movx;
    int newy = *prey + movy;
		
		
		
		PutChar(*prex*8,*prey*16,' ',Black,Black);
		
		 *prex = newx;
    *prey = newy;
		
		
		PutChar(newx*8,newy*16,'p',Yellow,Black);
		return dir;
}




int move(int* prex, int* prey, int dir, int width, int height, const int* walltiles, volatile char map[height][width]) {
    int movx = 0, movy = 0;

    // Determine the movement direction
    switch (dir) {
        case 0: // Up
            movx = 0;
            movy = -1;
            break;
        case 1: // Right
            movx = 1;
            movy = 0;
            break;
        case 2: // Down
            movx = 0;
            movy = 1;
            break;
        case 3: // Left
            movx = -1;
            movy = 0;
            break;
        default:
            return -1; // Invalid direction
    }

    // Calculate the new position
    int newx = *prex + movx;
    int newy = *prey + movy;

    // Check if the new position is within bounds
    if (newx < 0 || newx >= width || newy < 0 || newy >= height) {
        return -1; // Out of bounds
    }


    // Calculate the linear index for the 1D walltiles array
    int index = newy * width + newx;

    // Check if the new position is a wall
		
    if (walltiles[index] == 1) {
        return 0; // Move blocked by a wall
    }
		map[*prey][*prex]=' ';
		PutChar(*prex*8,*prey*16,' ',Black,Black);
    // Update position
    *prex = newx;
    *prey = newy;
		map[newy][newx]='p';
		PutChar(newx*8,newy*16,'p',Yellow,Black);
		
    return 1; // Move successful
}
