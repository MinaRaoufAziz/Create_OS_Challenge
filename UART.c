/*
 * UART.c
 *
 *  Created on: Oct 11, 2019
 *      Author: Rafaat
 */
#include "UART.h"

void UART_Init()
{
REG_UCSRB |=1<<RXEN|1<<TXEN|1<<RXCIE|1<<TXCIE;
REG_UCSRC |=1<<UCSZ1|1<<UCSZ0|1<<URSEL;
REG_UBRRL = 0x33 ;
}

void UART_Send(uint8 Char)
{
	//while(!(UCSRA&(1<<UDRE)));
	REG_UDR=Char;
}

uint8 UART_Recieve()
{
	while(!(REG_UCSRA&(1<<RXC)));
	return REG_UDR;
}

void UART_DeInit()
{
	REG_UCSRB &= ~(1<<RXEN|1<<TXEN|1<<RXCIE|1<<TXCIE);
	REG_UCSRC &= ~(1<<UCSZ1|1<<UCSZ0|1<<URSEL);
	REG_UBRRL = ~(0x33) ;
}
