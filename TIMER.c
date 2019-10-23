/*
 * TIMER.c
 *
 *  Created on: Sep 22, 2019
 *      Author: Rafaat
 */
#include "TIMER.h"
#include "registers.h"


status Timer_Init(uint8 Timer)
{
	uint8 Status=0;
	if(Timer < NUM_OF_TIMERS)
	{
		switch(Timer)
		{
		case TIMER_0 :
			if(Timer_arr[TIMER_0].Mode == NORMAL)
			{
				REG_TCCR0 &= ~(1<<WGM00);
				REG_TCCR0 &= ~(1<<WGM01);
				Status = OK;
			}else
			{
				Status = NOK;
			}

			break;

		case TIMER_1 :
			if(Timer_arr[TIMER_1].Mode == NORMAL)
			{
				REG_TCCR1A &= ~(1<<WGM10);
				REG_TCCR1A &= ~(1<<WGM11);
				REG_TCCR1B &= ~(1<<WGM12);
				REG_TCCR1B &= ~(1<<WGM13);
				Status = OK;

			}else
			{
				Status = NOK;
			}
			break;
		case TIMER_2 :
			if(Timer_arr[TIMER_2].Mode == NORMAL)
			{
				REG_TCCR2 &= ~(1<<WGM20);
				REG_TCCR2 &= ~(1<<WGM21);
				Status = OK;

			}else
			{
				Status = NOK;
			}
			break;
		}


	}else{
		Status= NOK;
	}
	return Status;
}

status Timer_SetPrescaler(uint8 Timer)
{ uint8 Status=0;
	switch(Timer)
	{
	case TIMER_0 :
		REG_TCCR0 |= Timer_arr[TIMER_0].Prescaler ;
		Status =OK;
		break;
	case TIMER_1 :
		REG_TCCR1B |= Timer_arr[TIMER_1].Prescaler ;
		Status =OK;
		break;
	case TIMER_2 :
		REG_TCCR2 |= Timer_arr[TIMER_2].Prescaler ;
		Status =OK;
		break;
	}
	return Status;
}
void Timer_Stop(uint8 Timer)
{
	switch(Timer)
	{
	case TIMER_0 :
		if(Timer_arr[TIMER_0].ISR == ISR_DS)
		{
			REG_TIMSK &= ~(1<<TOIE0);
		}
		else
		{

		}

		break;
	case TIMER_1 :
		if(Timer_arr[TIMER_1].ISR == ISR_EN)
		{
			REG_TIMSK &= ~(1<<TOIE1);
		}
		else
		{

		}
		break;
	case TIMER_2 :
		if(Timer_arr[TIMER_2].ISR == ISR_EN)
		{
			REG_TIMSK &= ~(1<<TOIE2);
		}
		else
		{

		}
		break;
	}

}
void Timer_Start(uint8 Timer)
{
	switch(Timer)
	{
	case TIMER_0 :
		if(Timer_arr[TIMER_0].ISR == ISR_EN)
		{
			REG_TIMSK |=1<<TOIE0;
			REG_TCNT0=0;
		}
		else
		{

		}

		break;
	case TIMER_1 :
		if(Timer_arr[TIMER_1].ISR == ISR_EN)
		{
			REG_TIMSK |=1<<TOIE1;
		}
		else
		{

		}
		break;
	case TIMER_2 :
		if(Timer_arr[TIMER_2].ISR == ISR_EN)
		{
			REG_TIMSK |=1<<TOIE2;
		}
		else
		{

		}
		break;
	}

}
