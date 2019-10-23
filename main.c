/*
 * main.c
 *
 *  Created on: Oct 22, 2019
 *      Author: Mina
 */

#include "sos.h"
#include "UART.h"
#include "registers.h"
#define TOG_BIT(var, bit) var ^= (1<<bit)
extern uint8 prescalar;
extern OS_Task_t All_Task_Buffer_Arr[MAX_TASKS];
extern OS_Task_t * All_Task_Buffer_Ptr;
extern OS_Task_t Ready_Task_Buffer_Arr[MAX_TASKS];
extern OS_Task_t * Ready_Task_Buffer_Ptr;
extern uint8 start_task_counter;

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
	if ((All_Task_Buffer_Ptr->Priority) == 1)
	{
		LED2_ON();

	}
	All_Task_Buffer_Ptr++;
	if ((All_Task_Buffer_Ptr->Periodicity) == 13)
	{
		if ((All_Task_Buffer_Ptr->Priority) == 2)
		{
			LED1_ON();
		}

	}
}
