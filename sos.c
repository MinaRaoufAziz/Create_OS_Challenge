/*
 * sos.c
 *
 *  Created on: Oct 22, 2019
 *      Author: Mina
 */


#include "sos.h"
#include "UART.h"
#include "registers.h"

uint8  prescalar;
static volatile uint8 ISR_counter = 0;
static volatile uint8 ISR_Flag = 0;
static uint8 start_task_counter;
OS_Task_t All_Task_Buffer_Arr[MAX_TASKS];
OS_Task_t * All_Task_Buffer_Ptr = &All_Task_Buffer_Arr;
OS_Task_t Ready_Task_Buffer_Arr[MAX_TASKS];
OS_Task_t * Ready_Task_Buffer_Ptr = &Ready_Task_Buffer_Arr;
OS_Task_t temp_struct;

OS_Tasks_Status_t SOS_Init(const OS_Congif_t * ConfigPtr)
{
	uint8 retval;
	if (NULL == ConfigPtr)
	{
		retval = NULLPTR_OS;
	}
	else
	{
		switch (ConfigPtr ->Timer_ID)
		{
		case TIMER_0:
			Timer_Init(TIMER_0);
			break;
		case TIMER_1:
			Timer_Init(TIMER_1);
			break;
		case TIMER_2:
			Timer_Init(TIMER_2);
			break;
		default:
			retval = INCORRECT_TIMER;
			break;
		}
		switch (ConfigPtr -> Systick_Time)
		{
		case 1:
			if ((TIMER_0 == ConfigPtr ->Timer_ID))
			{

				prescalar = CLK_DIV_8;
				/*The tovf will be 0.25 ms, we need to solve this issue in ISR
				 * by increamenting every 4 times */
				break;
			}
			else if ((TIMER_2 == ConfigPtr -> Timer_ID))
			{
				REG_DDRD = 0xff;
				prescalar = CLK_DIV_32;

				break;
			}
			else
			{
				retval = INVALID_PRESCALAR;
				break;
			}

		case 2:
			if ((TIMER_0 == ConfigPtr -> Timer_ID))
			{
				prescalar = CLK_DIV_64;
				/*The tovf will be 0.25 ms, we need to solve this issue in ISR
				 * by increamenting every 4 times */

				break;
			}
			else if ((TIMER_2 == ConfigPtr ->Timer_ID))
			{
				prescalar = CLK_DIV_64;
				break;
			}
			else
			{
				retval = INVALID_PRESCALAR;
				break;
			}
		default:
			retval = INVALID_PRESCALAR;
			break;
		}
	}
	return retval;
}

OS_Tasks_Status_t SOS_Create_Task (Func_Ptr_t task_Name, uint16 periodicity, uint8 priority)
{
	uint8 retval;
	if (start_task_counter <= MAX_TASKS)
	{
		static uint8 start_task_counter = 0;
		(All_Task_Buffer_Ptr [start_task_counter]) . Task_Name = task_Name;
		(All_Task_Buffer_Ptr [start_task_counter]) . Periodicity = periodicity;
		(All_Task_Buffer_Ptr [start_task_counter]) . Priority = priority;
		(All_Task_Buffer_Ptr [start_task_counter]) . Deadline = periodicity;
		(All_Task_Buffer_Ptr [start_task_counter]) . Func_State = CREATED;
		start_task_counter++;
		retval = DONE;
	}
	else
	{
		retval = OVF_TASKS_BUFFER_OS;
	}

	return retval;
}

OS_Tasks_Status_t SOS_Delete_Task (Func_Ptr_t Task_Name)
{
	uint8 counter;
	uint8 retval;
	for (counter = 0; counter < MAX_TASKS; counter++)
	{
		if (Task_Name == (All_Task_Buffer_Ptr + counter)->Task_Name)
		{
			(All_Task_Buffer_Ptr + counter)-> Task_Name = NULL;
			(All_Task_Buffer_Ptr + counter)-> Periodicity = DELETE;
			(All_Task_Buffer_Ptr + counter)-> Priority = DELETE;
			(All_Task_Buffer_Ptr + counter)-> Deadline = DELETE;
			(All_Task_Buffer_Ptr + counter)-> Func_State = DELETE;
			retval = DONE;
		}
		else
		{
			retval = INVALID_ARG;
		}
	}
	return retval;
}
void SOS_Run(void)
{
	uint8 all_task_counter;
	static uint8 ready_task_counter = 0;
	uint8 counter;
	uint8 counter_2;
	while(1)
	{
		for (all_task_counter = 0; all_task_counter < MAX_TASKS; all_task_counter++)
		{
			if (DELETE == ((All_Task_Buffer_Ptr + all_task_counter)->Func_State))
			{
				continue;
			}
			else
			{
				if (0 == (ISR_Flag % ((All_Task_Buffer_Ptr + all_task_counter)->Periodicity)))
				{
					Ready_Task_Buffer_Arr[ready_task_counter] = All_Task_Buffer_Arr[all_task_counter];
					Ready_Task_Buffer_Arr[ready_task_counter].Func_State = READY;
					ready_task_counter++;

				}
				else
				{
					continue;
				}
			}
		}
		for (counter = 0; counter < ready_task_counter; counter++)
		{
			for (counter_2 = counter+1; counter_2 < ready_task_counter; counter_2++)
			{
				if (Ready_Task_Buffer_Arr[counter].Priority > Ready_Task_Buffer_Arr[counter_2].Priority)
				{
					temp_struct = Ready_Task_Buffer_Arr[counter];
					Ready_Task_Buffer_Arr[counter] = Ready_Task_Buffer_Arr[counter_2];
					Ready_Task_Buffer_Arr[counter_2] = temp_struct;
				}
			}
		}
		for (counter = 0; counter < ready_task_counter; counter++)
		{
			*(Ready_Task_Buffer_Arr[counter].Task_Name);
		}
		ready_task_counter = 0;
	}

}

ISR(TIM0_OVF_vect)
{
	ISR_counter++;
	if (!(ISR_counter % 4))
	{
		ISR_Flag++;
	}
}
