#include "button.h"
#include "lpc17xx.h"
#include "timer/timer.h"
#include "GLCD/GLCD.h" 
#include "stdio.h"
#include "RIT/RIT.h"
#define MAP_WIDTH 30    // 240 pixels / 8px per character
#define MAP_HEIGHT 30

// Define the characters for the map
extern volatile char map[MAP_HEIGHT][MAP_WIDTH];
extern volatile int pause_;
void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
	
	
	if(pause_){
		  for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 2; j++) {
            int x = 13 + i;
            int y = MAP_HEIGHT / 2 + j;

            emptytile(x, y); // Clear the tile first

            // Draw based on the map character
            switch (map[y][x]) {
                case 'p':
                    drawPacMan(x, y);
                    break;
                case '*':
                    drawNormalPill(x, y);
                    break;
                case 'X':
                    drawBigPill(x, y);
                    break;
                case 'O':
                    drawGhost(x, y);
                    break;
                default:
                    break; // Do nothing for empty or unknown characters
            }
        }
    }
		
	//enable_RIT();	
	enable_timer(0);
	enable_timer(1);
	//enable_timer(2);
	//init_timer(3,0x07A120 /*0x17D7840*/); //Blinky timer doesn't actually work. Why?

	//enable_timer(3);
	
	pause_=0;
	}else if (pause_==0){
	//disable_RIT();	
	disable_timer(0);
	disable_timer(1);
	//disable_timer(3);
	//disable_timer(2);
	pause_=1;
	GUI_Text((13 *8),(MAP_HEIGHT/2)*8,(uint8_t *)"Pause",Yellow,White);	
	}
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
	
	
	
	
	
	
	
	/*
	if(pause){
		

		for(int i=0;i<5;i++){
			if(map[MAP_HEIGHT/2][13+i] =='P'){
			emptytile((13+i),MAP_HEIGHT/2);	
			drawPacMan((13+i),MAP_HEIGHT/2);}
			if(map[MAP_HEIGHT/2][13+i] =='*'){
			emptytile((13+i),MAP_HEIGHT/2);	
			drawNormalPill(13+i,MAP_HEIGHT/2);}	
			if(map[MAP_HEIGHT/2][13+i] =='X'){
			emptytile((13+i),MAP_HEIGHT/2);	
			drawBigPill(13+i,MAP_HEIGHT/2);}
			if(map[MAP_HEIGHT/2][13+i] =='O'){
			emptytile((13+i),MAP_HEIGHT/2);	
			drawGhost(13+i,MAP_HEIGHT/2);}	
			
	//PutChar((13+i)*8,(MAP_HEIGHT/2)*16, map[MAP_HEIGHT/2][13+i],Yellow,Black);
		}

	enable_timer(0);
	enable_timer(1);
	enable_timer(2);


	enable_timer(3);
	pause=0;
	}else{
	disable_timer(0);
	disable_timer(1);
	disable_timer(2);
	disable_timer(3);
	pause=1;
	GUI_Text((13 *8),(MAP_HEIGHT/2)*8,(uint8_t *)"Pause",Yellow,White);	
	}
	LPC_SC->EXTINT &= (1 << 0); */     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


