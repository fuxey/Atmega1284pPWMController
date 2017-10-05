


#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include "Uart.h"


static volatile uint8_t rcvBufferPosCntr = 0;
volatile uint8_t uartRcvFlag =0;
static uint8_t inbuf[INBUF_SIZE];


uint8_t * getUartRcvPtr(void){
	return &inbuf;
}


void printSyncronousOnUart(uint8_t *str,uint16_t len) {
	uint16_t i = 0;
	for(i=0; i < len; i++){
		putcUart(*str);
		str++;
	}
}


void initUart(void){
	
	UBRR0 = UBRR_VAL;
	UCSR0B = (1 << TXEN0) | (1<< RXEN0) | (1<< RXCIE0);
	// Frame Format: Asynchron 8N1
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	UCSR0A = (1<<RXC0) | (1<<TXC0);
	resetRcvFlagAndClearRcvBuffer();
	sei();
}


//used for printf
int putcUart(uint8_t c) {
	while (!(UCSR0A & (1<<UDRE0)))
	{
	}
	UDR0 = c;
	return 0;
}




int putCharUart( char c, FILE *stream ){
	if( c == '\n' )
	putCharUart( '\r', stream );
	while (!(UCSR0A & (1<<UDRE0)))
	{
	}
	UDR0 = c;
	return 0;
}


void putStringOnUart (char *s){
	while (*s){
		putcUart(*s);
		s++;
	}
}


static void putRxUartDataToFifoBuffer(uint8_t data){
	uartRcvFlag = 1;
	if(rcvBufferPosCntr < INBUF_SIZE){
		inbuf[rcvBufferPosCntr]=data;
		rcvBufferPosCntr++;
	}else{
		rcvBufferPosCntr=0;
		inbuf[rcvBufferPosCntr]=data;
	}
}


void resetRcvFlagAndClearRcvBuffer(void){
	uartRcvFlag =0;
	rcvBufferPosCntr =0;
	(void)memset(inbuf,0,INBUF_SIZE-1);
}


uint8_t isUartDataReceived(void){
	return uartRcvFlag;
}

ISR(USART_RX_vect)
{
	putRxUartDataToFifoBuffer(UDR0);
}
