
#include "GameData/PlayerInfo.h"
extern int score;
volatile char scorechar[6];
extern int lives;
volatile char liveschar[3];
extern int power;
void drawScore(){
		GUI_Text(0,19*16,(uint8_t *)scorechar,White,Black);

};
void drawLives(){
		
};


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
		if(cointiles[index] == 1){
			score+=10;
			cointiles[index] = 0;
			sprintf(scorechar,
               "%d", score);
			drawScore();
			
		}
		
		if(newx==0 && newy==8){
		map[*prey][*prex]=' ';
		PutChar(*prex*8,*prey*16,' ',Black,Black);
		
			
		
		newx=29;
		*prex = newx;
    *prey = newy;
		map[newy][newx]='p';
		PutChar(newx*8,newy*16,'p',Yellow,Black);
			return 1;
		}
		
		
		
		if(newx==29 && newy==8){
		map[*prey][*prex]=' ';
		PutChar(*prex*8,*prey*16,' ',Black,Black);
		
			
		
		newx=0;
		*prex = newx;
    *prey = newy;
		map[newy][newx]='p';
		PutChar(newx*8,newy*16,'p',Yellow,Black);
			return 1;
		}
		
			if(poweruptiles[index] == 1){
			score+=50;
			power++;
			poweruptiles[index] = 0;
			sprintf(scorechar,
               "%d", score);
			drawScore();
			
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
