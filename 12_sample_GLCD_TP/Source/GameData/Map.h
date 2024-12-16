#ifndef MAP_H
#define MAP_H

#define MAP_WIDTH 30    // 240 pixels / 8px per character
#define MAP_HEIGHT 18
volatile int emptytiles[MAP_HEIGHT*MAP_WIDTH];
volatile int wallstiles[MAP_HEIGHT*MAP_WIDTH];
volatile int cointiles[MAP_HEIGHT*MAP_WIDTH];
volatile int poweruptiles[MAP_HEIGHT*MAP_WIDTH];
volatile int teleportlocation[MAP_HEIGHT*MAP_WIDTH];

volatile int time=60;
volatile int score=0;
volatile int lives=1;


void initialize(int height, int width, 
                int emptytiles[height * width], 
                int wallstiles[height * width],
                int cointiles[height * width],
                int poweruptiles[height * width],
                char map[height][width]);
								
								
#endif // PLAYER_INFO_H								