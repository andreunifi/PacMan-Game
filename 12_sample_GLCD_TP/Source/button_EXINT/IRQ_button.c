#include "button.h"
#include "lpc17xx.h"
#include "timer/timer.h"
#include "GLCD/GLCD.h" 
#define MAP_WIDTH 30    // 240 pixels / 8px per character
#define MAP_HEIGHT 18

// Define the characters for the map
extern volatile char map[MAP_HEIGHT][MAP_WIDTH];
extern int pause;
void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
	if(pause){
		for(int i=0;i<5;i++){
	PutChar((13+i)*8,(MAP_HEIGHT/2)*16, map[MAP_HEIGHT/2][13+i],Yellow,Black);
		
	}
	enable_timer(0);
	enable_timer(1);
	enable_timer(2);
	init_timer(3,/*0x07A120*/ 0x225510 ); //Blinky timer doesn't actually work. Why?

	enable_timer(3);
	pause=0;
	}else{
	disable_timer(0);
	disable_timer(1);
	disable_timer(2);
	disable_timer(3);
	pause=1;
	GUI_Text((13 *8),(MAP_HEIGHT/2)*16,(uint8_t *)"Pause",Yellow,White);	
	}
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


