/*
 * USART.c
 *
 * Created: 10/12/2023 14:27:14
 *  Author: Eslam
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include "USART.h"
#include "std_macros.h"
#include <util/delay.h>

void UART_vInit(unsigned long baud){
//	SET_BIT(UCSRA,U2X);

	unsigned short UBRR ;
	UBRR=(F_CPU/(16*baud))-1 ;
	UBRRH=(unsigned char)(UBRR>>8);
	UBRRL=(unsigned char)UBRR;
	/*2 - Enable USART Sender & Receiver*/
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
	/*3 - Choose number of data bits to be sent,parity and stop bits from UCSRC
	, We will work with 8 bits data,1 stop bit and no parity bits*/
	UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
}

void UART_vSendData(char data){
	
	while(READ_BIT(UCSRA,UDRE)==0);
	UDR=data;
}

char UART_u8ReceiveData(void){
	while(READ_BIT(UCSRA,RXC)==0);
	return UDR;
}

void UART_vSendstring( char *ptr)
{
	while(*ptr!=0)
	{
		UART_vSendData(*ptr);
		ptr++;
		_delay_ms(10);
	}
}