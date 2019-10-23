/*
 * Reg.h
 *
 *  Created on: Sep 20, 2019
 *      Author: Rafaat
 */

#ifndef REG_H_
#define REG_H_

#include "stdtypes.h"

#define NULL_PTR (void*)0
/* Definition for PORTA Registers */
#define PORTA_REG	(*(volatile uint8 * const)0x003B)
#define DDRA_REG	(*(volatile uint8 * const)0x003A)
#define PINA_REG 	(*(volatile const uint8 * const)0x0039)

/* Definition for PORTB Registers */
#define PORTB_REG	(*(volatile uint8 * const)0x0038)
#define DDRB_REG	(*(volatile uint8 * const)0x0037)
#define PINB_REG 	(*(volatile const uint8 * const)0x0036)

/* Definition for PORTC Registers */
#define PORTC_REG	(*(volatile uint8 * const)0x0035)
#define DDRC_REG	(*(volatile uint8 * const)0x0034)
#define PINC_REG 	(*(volatile const uint8 * const)0x0033)

/* Definition for PORTD Registers */
#define PORTD_REG	(*(volatile uint8 * const)0x0032)
#define DDRD_REG	(*(volatile uint8 * const)0x0031)
#define PIND_REG 	(*(volatile const uint8 * const)0x0030)

/* Definition for Timer Registers */
#define TCCR0	  (*((volatile uint8*)0x53))
#define TIMSK 	  (*((volatile uint8*)0x59))
#define TIFR  	  (*((volatile uint8*)0x58))
#define OCR0  	  (*((volatile uint8*)0x5c))
#define TCNT0 	  (*((volatile uint8*)0x52))
#define SREG  	  (*((volatile uint8*)0x5f))
#define MCUCR  	  (*((volatile uint8*)0x55))
#define MCUCSR    (*((volatile uint8*)0x54))
#define GICR      (*((volatile uint8*)0x5B))
#define GIFR      (*((volatile uint8*)0x5A))
#define TCCR1A    (*((volatile uint8*)0x4F))
#define TCCR1B    (*((volatile uint8*)0x4E))
#define TCNT1H    (*((volatile uint8*)0x4D))
#define TCNT1L    (*((volatile uint8*)0x4C))
#define TCNT1     (*((volatile uint16*)0x4C))
#define OCR1AH    (*((volatile uint8*)0x4B))
#define OCR1AL    (*((volatile uint8*)0x4A))
#define OCR1BH    (*((volatile uint8*)0x49))
#define OCR1BL    (*((volatile uint8*)0x48))
#define ICR1H     (*((volatile uint8*)0x47))
#define ICR1L     (*((volatile uint8*)0x46))
#define ICR1  	  (*((volatile uint16*)0x46))
#define TIMSK  	  (*((volatile uint8*)0x59))
#define TIFR  	  (*((volatile uint8*)0x58))
#define OCR1A  	  (*((volatile uint8*)0x4A))
#define TCCR2     (*((volatile uint8*)0x45))
#define TCNT2     (*((volatile uint8*)0x44))
#define OCR2      (*((volatile uint8*)0x43))
#define WGM12   3

/* bit 5 reserved */
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0
/* TCCR2 */
#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0
/* TCCR1A */
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0

#endif /* REG_H_ */
