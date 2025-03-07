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
#include "CAN/CAN.h"
#include "adc/adc.h"
#include "GameData/GhostAI.h"

#define MAP_WIDTH 30    // 240 pixels / 8px per character
#define MAP_HEIGHT 30

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
extern int lives;

extern int score;
extern PlayerInfo player;
extern volatile char map[MAP_HEIGHT][MAP_WIDTH];
extern int emptytiles[MAP_HEIGHT*MAP_WIDTH];
extern int wallstiles[MAP_HEIGHT*MAP_WIDTH];
extern int cointiles[MAP_HEIGHT*MAP_WIDTH];
extern int poweruptiles[MAP_HEIGHT*MAP_WIDTH];
extern int teleportlocation[MAP_HEIGHT*MAP_WIDTH];
extern GhostInfo blinkly;



uint16_t SinTable[45] =                                       /* ?????                       */
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};







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
					drawBigPill(x,y);
					//PutChar(x*8,y*16,'X',Red,Black);
				}else{
				poweruptiles[index]=1;
				map[y][x]='X';
				drawBigPill(x,y);
				//PutChar(x*8,y*16,'X',Red,Black);
				}
				power--;
			}
			
	}

};	

void TIMER0_IRQHandler (void) //this is the main game tick()
{
	
	//player movement code
		
	move(&player.x, &player.y, dir, MAP_WIDTH,MAP_HEIGHT, wallstiles,map);
	

	//blinkly movement code
	
	 static int counter100ns = 0; // Counter for 100 ns actions
    static int counter50ns = 0;  // Counter for 50 ns actions
    static int counter20ns = 0;  // Counter for 20 ns actions

    // Increment counters with each interrupt
    counter100ns += 10;  // 10 ns per interrupt
    counter50ns += 10;
    counter20ns += 10;
		
	
		
		
	
		
    // Difficulty logic based on 'time'
    if (time > 45) {
        // Execute action for 100 ns interval
        if (counter100ns >=60) {
            // Action for difficulty 1
           moveGhost(&blinkly.prevx,&blinkly.prevy,MAP_WIDTH,MAP_HEIGHT,wallstiles,map,blinkly.status,player.x,player.y);
						//PutChar(x*8,y*16,'M',Green,Black);
            counter100ns = 0; // Reset counter
        }
    } else if (time >= 30 && time < 45) {
        // Execute action for 50 ns interval
        if (counter50ns >= 40) {
            // Action for difficulty 2
            moveGhost(&blinkly.prevx,&blinkly.prevy,MAP_WIDTH,MAP_HEIGHT,wallstiles,map,blinkly.status,player.x,player.y);
						//PutChar(x*8,y*16,'K',Green,Black);
            counter50ns = 0; // Reset counter
        }
    } else if (time < 30  ) {
        // Execute action for 20 ns interval
        if (counter20ns >= 20) {
            // Action for difficulty 3
            moveGhost(&blinkly.prevx,&blinkly.prevy,MAP_WIDTH,MAP_HEIGHT,wallstiles,map,blinkly.status,player.x,player.y);
						//PutChar(x*8,y*16,'D',Green,Black);
            counter20ns = 0; // Reset counter
        }
    }
		
		if(blinkly.x == player.x && blinkly.y == player.y && blinkly.status==1){
			if(lives>1){
			map[player.y][player.x]=' ';
			emptytile(player.x,player.y);
			//PutChar(player.x*8,player.y*16,' ',Black,Black);	
				
			player.x=1;
			player.y=1;				
			map[1][1]='P';
			drawPacMan(player.x,player.y);
			//PutChar(player.x*8,player.y*16,'p',Yellow,Black);
    // Update position


			
			


			map[blinkly.y][blinkly.x]=' ';

			blinkly.prevx=14;
			blinkly.prevy=12;
			blinkly.x=14;
			blinkly.y=12;
			map[14][12]='O';
			drawGhost(blinkly.x,blinkly.y);
			//PutChar(blinkly.x*8,blinkly.y*16,'O',Red,Black);			

			
			
			

		
		if (lives == 2)
			emptytile(28,38);
		
		if (lives == 3)
			emptytile(27,38);
			
			
			
			lives--;
			
			
			
			
			}else{
				disable_timer(0);
				disable_timer(1);
				disable_timer(2);
				disable_timer(3);
				GUI_Text((11 *8),(MAP_HEIGHT/2)*16,(uint8_t *)"Game Over!",Red,White);
			}
			
		}
 
		
	
	
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
void TIMER1_IRQHandler (void) //used to generate the countdown timer. #todo: can be refractored.
{
	if(time>0){
	time--;
  sprintf(timechar,
               "%d", time);
	drawTime();
		
	
	}
	
	if(time==0){
	disable_timer(0);
	disable_timer(1);
	disable_timer(2);
	disable_timer(3);
		
		GUI_Text((11 *8),(MAP_HEIGHT/2)*16,(uint8_t *)"Game Over!",Red,White);
	}	
  
	
	CAN_TxMsg.data[0] = (time & 0xFF); 
	CAN_TxMsg.data[1] = 	lives & 0xFF;
	CAN_TxMsg.data[2] = (score & 0x00FF ); 
	CAN_TxMsg.data[3] = (score & 0xFF00 ) >> 8  ;
	CAN_TxMsg.len = 4;
	CAN_TxMsg.id = 2;
	CAN_TxMsg.format = STANDARD_FORMAT;
	CAN_TxMsg.type = DATA_FRAME;
	CAN_wrMsg (1, &CAN_TxMsg);         
	

	if(blinkly.status==2){
		if(blinkly.remainingtime >0){
		blinkly.remainingtime--;
		}else{
		blinkly.status=1;
		blinkly.remainingtime=10;	
		}
	
		
	}
	
	if(blinkly.status==3 ){
		if(blinkly.respawntime > 0){
		blinkly.respawntime--;
		}else{
		blinkly.prevx=14;
		blinkly.prevy=12;
		blinkly.x=14;
		blinkly.y=12;
			//TODO: check this code
		map[10][2]='O';
		drawGhost(14,12);	
		
			
		blinkly.status=1;
		blinkly.respawntime=3;	
		}
	
	}
	
	generatePower();
	
//	static int sineticks=0;
//	/* DAC management */	
//	static int currentValue; 
//	currentValue = SinTable[sineticks];
//	currentValue -= 410;
//	currentValue /= 1;
//	currentValue += 410;
//	LPC_DAC->DACR = currentValue <<6;
//	sineticks++;
//	if(sineticks==45) sineticks=0;
	
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER2_IRQHandler (void)
{
	static int sineticks=0;
	/* DAC management */	
	static int currentValue; 
	currentValue = SinTable[sineticks];
	currentValue -= 410;
	currentValue /= 1;
	currentValue += 410;
	LPC_DAC->DACR = currentValue <<6;
	sineticks++;
	if(sineticks==45) sineticks=0;
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER3_IRQHandler (void){
		
	
		disable_timer(2);
		//disable_timer(3);
		LPC_TIM3->IR = 1;
};

/******************************************************************************
**                            End Of File
******************************************************************************/
