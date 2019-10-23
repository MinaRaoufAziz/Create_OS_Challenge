/*
 * main.c
 *
 *  Created on: Oct 22, 2019
 *      Author: Mina
 */

#include "sos.h"
#include "registers.h"


void LED1_ON()
{
	REG_DDRB = 0x10;
	REG_PORTB = 0x10;
}

void LED2_ON()
{
	REG_DDRB = 0x20;
	REG_PORTB = 0x20;
}




int main ()
{
	OS_Congif_t SOS_Cfg;
	SOS_Cfg.Timer_ID = TIMER_0;
	SOS_Cfg.Systick_Time = 1;
	const OS_Congif_t * Cfg_Ptr = &SOS_Cfg;
	SOS_Init (Cfg_Ptr);
	SOS_Create_Task(LED1_ON, 20, 1);
	SOS_Create_Task(LED2_ON, 13, 2);
	Timer_SetPrescaler(Cfg_Ptr->Timer_ID);
	Timer_Start(Cfg_Ptr->Timer_ID);

}
