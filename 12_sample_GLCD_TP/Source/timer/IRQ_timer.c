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


extern int dir;
extern PlayerInfo player;
extern volatile char map[MAP_HEIGHT][MAP_WIDTH];
extern int emptytiles[MAP_HEIGHT*MAP_WIDTH];
extern int wallstiles[MAP_HEIGHT*MAP_WIDTH];
extern int cointiles[MAP_HEIGHT*MAP_WIDTH];
extern int poweruptiles[MAP_HEIGHT*MAP_WIDTH];
extern int teleportlocation[MAP_HEIGHT*MAP_WIDTH];
void TIMER0_IRQHandler (void)
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
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
