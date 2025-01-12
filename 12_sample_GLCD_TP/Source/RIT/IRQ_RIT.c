/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "GameData/PlayerInfo.h"
#include "timer/timer.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


#define MAP_WIDTH 30    // 240 pixels / 8px per character
#define MAP_HEIGHT 18


//TODO: fix if joystick has chosen a non regular wat SW,NW;SE;NE

volatile int down=0;
extern int isPaused;

int dir=-1;
void RIT_IRQHandler (void)
{	
	static int ext1=0;
	static int up=0;
	static int position=0;	
	static int left=0;
	static int right=0;
	
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
		/* Joytick UP pressed */
		up++;
		switch(up){
			case 1:
				dir=0;
				LED_Out(0);
				LED_On(3);
				//move2(&player.x, &player.y, 0, MAP_WIDTH,MAP_HEIGHT);
				
			
				
				break;
			case 60:	//3sec = 3000ms/50ms = 60
				//move(&player.x, &player.y, 0, MAP_WIDTH,MAP_HEIGHT, wallstiles,map);
				break;
			default:
				break;
		}
	}
	else{
			up=0;
	}
	
	
	
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	
		/* Joytick LEFT pressed */
		left++;
		switch(left){
			case 1:
				LED_Out(0);
				LED_On(4);
				dir=3;
				
			//move2(&player.x, &player.y, 3, MAP_WIDTH,MAP_HEIGHT);
				break;
			case 60:	//3sec = 3000ms/50ms = 60
				//move(&player.x, &player.y, 3, MAP_WIDTH,MAP_HEIGHT, wallstiles,map);
				break;
			default:
				break;
		}
	}
	else{
			left=0;
	}
	
	
	
		if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	
		/* Joytick RIGHT pressed */
		right++;
		switch(right){
			case 1:
				LED_Out(0);
				LED_On(5);
				dir=1;
				
				//move2(&player.x, &player.y, 1, MAP_WIDTH,MAP_HEIGHT);
				break;
			case 60:	//3sec = 3000ms/50ms = 60
				//move(&player.x, &player.y, 1, MAP_WIDTH,MAP_HEIGHT, wallstiles,map);
				break;
			default:
				break;
		}
	}
	else{
			right=0;
	}
	
		
		if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
		/* Joytick DOWN pressed */
		down++;
		switch(down){
			case 1:
				LED_Out(0);
				LED_On(0);
				dir=2;
				
				//move2(&player.x, &player.y, 2, MAP_WIDTH,MAP_HEIGHT);
				break;
			case 60:	//3sec = 3000ms/50ms = 60
				//move(&player.x, &player.y, 2, MAP_WIDTH,MAP_HEIGHT, wallstiles,map);
				break;
			default:
				break;
		}
	}
	else{
			down=0;
	}
	

	
	


	
	
	reset_RIT();

  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
