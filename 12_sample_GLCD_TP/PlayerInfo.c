
#include "GameData/PlayerInfo.h"
extern int score;
volatile char scorechar[6];
extern int lives;
extern GhostInfo blinkly;
volatile char liveschar[3];
extern int power;
extern int count;
void drawScore(){
		GUI_Text(0,19*16,(uint8_t *)scorechar,White,Black);

};
void drawLives(){
		if(lives == 1)
			GUI_Text(27*8,19*16,(uint8_t *)"P",Yellow,Black);
		
		if (lives == 2)
			GUI_Text(27*8,19*16,(uint8_t *)"PP",Yellow,Black);
		
		if (lives == 3)
			GUI_Text(27*8,19*16,(uint8_t *)"PPP",Yellow,Black);
};





int move(int* prex, int* prey, int dir, int width, int height, const int* walltiles, volatile char map[height][width]) {
    int movx = 0, movy = 0;
		int lastscore = score;
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
			count--;
			
			if(count==0 && power == 0){
			disable_timer(0);
			disable_timer(1);
			disable_timer(2);	
			disable_timer(3);	
			GUI_Text((11 *8),(MAP_HEIGHT/2)*16,(uint8_t *)"You win!",Green,White);
			}
			
			if((int)(score / 1000 ) - (int)(lastscore / 1000) == 1)
				if(lives <3){
				lives++;
					drawLives();
				}
					
				
			
		}
		
		if(newx==0 && newy==9){
		map[*prey][*prex]=' ';
		PutChar(*prex*8,*prey*16,' ',Black,Black);
		
			
		
		newx=29;
		*prex = newx;
    *prey = newy;
		map[newy][newx]='p';
		PutChar(newx*8,newy*16,'p',Yellow,Black);
			return 1;
		}
		
		
		
		if(newx==29 && newy==9){
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
			poweruptiles[index] = 0;
			sprintf(scorechar,
               "%d", score);
			drawScore();
			blinkly.status=2;
			blinkly.remainingtime=10;
			if((int)(score / 1000 ) - (int)(lastscore / 1000) == 1)
				if(lives <3){
				lives++;
					drawLives();
				}
			
		}
		
		
		
		
		map[*prey][*prex]=' ';
		PutChar(*prex*8,*prey*16,' ',Black,Black);
    // Update position
    *prex = newx;
    *prey = newy;
		map[newy][newx]='p';
		PutChar(newx*8,newy*16,'p',Yellow,Black);
		
		
		if(newx == blinkly.x && newy == blinkly.y && blinkly.status==2){
			blinkly.status=3;
			blinkly.remainingtime=10;
			
			
	
    // Update position after being eaten
				

				
		}
		
		
    return 1; // Move successful
}
