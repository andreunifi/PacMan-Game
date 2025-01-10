/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "GameData/PlayerInfo.h"
#include "joystick/joystick.h"
#include "RIT/RIT.h"
#include "CAN/CAN.h"
#include "GameData/GhostAI.h"
#include "button.h"

#define MAP_WIDTH 30    // 240 pixels / 8px per character
#define MAP_HEIGHT 18

// Define the characters for the map
extern volatile char map[MAP_HEIGHT][MAP_WIDTH];

extern volatile int emptytiles[MAP_HEIGHT*MAP_WIDTH];
extern volatile int wallstiles[MAP_HEIGHT*MAP_WIDTH];

extern void initialize(int height, int width, 
                int emptytiles[height * width], 
                int wallstiles[height * width],
                int cointiles[height * width],
                int poweruptiles[height * width],
                char map[height][width]);

PlayerInfo player;
GhostInfo blinkly;
volatile int pause=1;
void initializeMap(){
for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
			
			char tile = map[y][x];
      
      // Determine the color based on the tile character
      uint16_t color;
      if (tile == '#') {
        color = Blue ;  // Wall
      } else if (tile == ' ') {
          // Path
				tile=' ';
      } else if (tile == 'P') {
        color = Yellow;  // Pac-Man
				player.x=x;
				player.y=y;
      } else if(tile == '*'){
				
        color = Yellow;  // Default to path color
				
      }else if(tile == 'O'){
			color = Red;
			}else if(tile == 'x'){
			tile = ' ';
			}
			PutChar( x*8, y*16, tile, color, Black);
		}
		}
}





uint16_t screenwidht=240;
uint16_t screenheight=320;


#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	CAN_Init();
	
	blinkly.x=2;
	blinkly.y=9;
	blinkly.status=1;
	blinkly.prevx=2;
	blinkly.prevy=9;
	blinkly.remainingtime=10;
	blinkly.respawntime=3;
	player.lives=1;
	player.x=1;
	player.y=1;
	
	joystick_init();
  LCD_Initialization();
	
 
	//TouchPanel_Calibrate();
	
	LCD_Clear(Black);

	
	//PutChar(0,0,'X',Red,Black);
	//PutChar(0,16,'X',Red,Black);

	initialize(MAP_HEIGHT,MAP_WIDTH,emptytiles, 
                wallstiles,
                cointiles,
                poweruptiles,
                map);
	initializeMap();
	GUI_Text(0,18*16,(uint8_t *)"Score",White,Black);
	
	
	GUI_Text(14*8,18*16,(uint8_t *)"Time",White,Black);
	GUI_Text(2*8,19*16,(uint8_t *)"0",White,Black);
	
	GUI_Text(25*8,18*16,(uint8_t *)"Lives",White,Black);
	GUI_Text(27*8,19*16,(uint8_t *)"P",Yellow,Black);
	
	//initializeMap();
	joystick_init();
	
	init_RIT(0x004C4B40);		//old value, 50 ms
	/* RIT Initialization 50 msec       	*/
	//init_RIT(0x004C4BA4);
	enable_RIT();													/* RIT enabled												*/
	
		
	//GUI_Text(0, 0, (uint8_t *) " touch here : 1 sec to clear  ", Red, White);
	
	//LCD_DrawLine(0, 0, 200, 200, White);
	//init_timer(0, 0x1312D0 ); 						/* 50ms * 25MHz = 1.25*10^6 = 0x1312D0 */
	init_timer(0, 0x225510 ); 						  /* 1ms * 25MHz = 25*10^3 = 0x6108 */
	
	
	init_timer(1,0x17D7840); //60 seconds timer
	
	
	//init_timer(2,0x225510); //60 seconds timer
	
	
	init_timer(3,0x225510); //60 seconds timer
	//enable_timer(3);
	BUTTON_init();
	GUI_Text((11 *8),(MAP_HEIGHT/2)*16,(uint8_t *)"Pause",Yellow,White);
	
	
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		
		
			
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
