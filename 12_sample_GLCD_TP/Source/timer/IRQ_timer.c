/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "LPC17xx.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include <stdio.h> /*for sprintf*/
#include "GameData/PlayerInfo.h"
#define MAP_WIDTH 30    // 240 pixels / 8px per character
#define MAP_HEIGHT 18

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern int time;
volatile char timechar[3];
extern int power;
extern int dir;
extern PlayerInfo player;
extern volatile char map[MAP_HEIGHT][MAP_WIDTH];
extern int emptytiles[MAP_HEIGHT*MAP_WIDTH];
extern int wallstiles[MAP_HEIGHT*MAP_WIDTH];
extern int cointiles[MAP_HEIGHT*MAP_WIDTH];
extern int poweruptiles[MAP_HEIGHT*MAP_WIDTH];
extern int teleportlocation[MAP_HEIGHT*MAP_WIDTH];

void drawTime(){
GUI_Text(15*8,19*16,(uint8_t *)timechar,White,Black);
};

void generatePower(){
	   int value = rand() % (1 + 1);
		if(value && power>0){
			int x=rand() % (30 + 1);
			int y= rand() % (18 + 1);
			int index = y * MAP_WIDTH + x;
			if(emptytiles[index] && poweruptiles[index]==0 && teleportlocation[index]==0 ){
				if(cointiles[index]==1){
					cointiles[index]=0;
					poweruptiles[index]=1;
					map[y][x]='X';
					PutChar(x*8,y*16,'X',Red,Black);
				}else{
				poweruptiles[index]=1;
				map[y][x]='X';
				PutChar(x*8,y*16,'X',Red,Black);
				}
				power--;
			}
			
	}

};	

void TIMER0_IRQHandler (void) //this is the main game tick()
{
	
	
		
	move(&player.x, &player.y, dir, MAP_WIDTH,MAP_HEIGHT, wallstiles,map);
	
	
	
	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	if(time>0){
	time--;
  sprintf(timechar,
               "%d", time);
	drawTime();
		
	
	}
	
	if(time==0){
	disable_timer(0);
		GUI_Text((11 *8),(MAP_HEIGHT/2)*16,(uint8_t *)"Game Over!",Red,White);
	}	
  
	
	
	
	
	
	generatePower();
	
	
	
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER2_IRQHandler (void)
{
	
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}



/******************************************************************************
**                            End Of File
******************************************************************************/
