/*
 * sos.h
 *
 *  Created on: Oct 22, 2019
 *      Author: Mina
 */

#ifndef SOS_H_
#define SOS_H_

#include "timer.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include "UART.h"
#define MAX_TASKS 	5
#define TOG_BIT(var, bit) var ^= (1<<bit)

typedef enum {OVF_TASKS_BUFFER_OS = -9, NULLPTR_OS, INCORRECT_TIMER, INVALID_PRESCALAR,INVALID_ARG ,DONE = 1}OS_Tasks_Status_t;

typedef struct
{
	uint8 Timer_ID;
	uint8 Systick_Time;
}OS_Congif_t;
typedef void (*Func_Ptr_t)(void);

typedef enum {CREATED,READY, WAIT, RUN, DELETE}State_t;
typedef struct
{
	Func_Ptr_t Task_Name; // function name
	uint16 Periodicity;
	uint8 Priority;
	State_t Func_State;
	uint16 Deadline;
}OS_Task_t;

OS_Task_t Tasks_Stack [MAX_TASKS];

OS_Tasks_Status_t SOS_Init(const OS_Congif_t * ConfigPtr);
void SOS_Run(void);
OS_Tasks_Status_t SOS_Create_Task (Func_Ptr_t Task_Name, uint16 Periodicity, uint8 Priority);
OS_Tasks_Status_t SOS_Delete_Task (Func_Ptr_t Task_Name);


#endif /* SOS_H_ */
