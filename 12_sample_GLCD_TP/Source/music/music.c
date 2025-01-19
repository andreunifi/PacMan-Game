#include "music.h"


void playNote(NOTE note)
{
	if(note.freq != pause_music)
	{
		reset_timer(2);
		init_timer(2, note.freq);
		//LPC_TIM2->MCR = 3; //magic numbers
		enable_timer(2);
	}
	reset_timer(3);
	init_timer(3, note.duration);
	//LPC_TIM3->MCR = 7;	 //MAgic number
	enable_timer(3);
}

BOOL isNotePlaying(void)
{
	return ((LPC_TIM2->TCR != 0) || (LPC_TIM3->TCR != 0));
}
