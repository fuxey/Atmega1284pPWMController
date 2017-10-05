/*
 * FanControl.cpp
 *
 * Created: 08.04.2017 18:15:58
 * Author : DF
 */ 
#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "Uart/Debugmessage.h"
#include "Uart/SerialInterface0.h"

#include "PWM/Pwm.h"
#ifdef __cplusplus
}
#endif

static uint8_t pwmCnt = 0;


 void UART_RECV_TASK(void){
	 //print_buffer();
	 uint8_t *ptr;
	 char *arg;
	 uint16_t argval=0;
	 
	 ptr = getUartRcvPtr();

	 arg = strstr((const char *)ptr,"+++");
	 if(arg != NULL){
		 
		 argval = pwmCnt;
		 argval++;
		 if(argval > 255)
		 argval = 255;
		 
		 pwmCnt = (uint8_t) argval;
		 DEBUGMESSAGE("FOUND '+++'(increment) CMD! pwmCnt:%d\n",pwmCnt);
		 SetAllPwmChannelToDutyCycle(pwmCnt);
		 resetRcvFlagAndClearRcvBuffer();
		 return;
	 }
	 
	 arg = strstr((const char *)ptr,"---");
	 if(arg != NULL){
		 DEBUGMESSAGE("FOUND '---'(decrement) CMD! pwmCnt:%d\n",pwmCnt);
		 argval = pwmCnt;
		 argval--;
		 if(argval <=  0|| argval > 255)
		 argval = 0;
		 
		 pwmCnt = (uint8_t) argval;
		 SetAllPwmChannelToDutyCycle(pwmCnt);
		 resetRcvFlagAndClearRcvBuffer();
		 return;
	 }
	 
	 arg = strstr((const char *)ptr,"FLUSH");
	 if(arg != NULL){
		 DEBUGMESSAGE("FOUND 'FLUSH' CMD!\n");
		 resetRcvFlagAndClearRcvBuffer();
		 return;
	 }
	 
 }

int main(void)
{
	initUart();
	setOutputhandler(putcUart);
	initPwmTimer((uint32_t)100000);//try to init with 50khz
	SetAllPwmChannelToDutyCycle(50);
	DEBUGMESSAGE("INIT Uart and Timer!\n");
    /* Replace with your application code */
    while (1) 
    {
		if(isUartDataReceived()){
			UART_RECV_TASK();
		}		
    }
}

