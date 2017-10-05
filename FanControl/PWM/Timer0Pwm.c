





#include "Timer0Pwm.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../Uart/Debugmessage.h"


static void PinConfig(void){
	DDRB |= (1<<PORTB3)|(1<<PORTB4);
}


void initTimer0ToPwm(void){
	
	TCCR0A = 0;
	TCCR0B = 0;
	TCCR0A |= (1<<COM0B1) |(1<<COM0A1);
	TCCR0A |= (1<<WGM00)|(1<<WGM01); //phase correct pwm 8bit
	OCR0A = 128;
	OCR0B = 128;
	TCCR0B |= (1<<CS00);//|(1<<WGM02);
	PinConfig();
}


static void setPwmDutyChannelB(uint8_t duty){
	DEBUGMESSAGE("SetTim0ChB:%d",duty);
	OCR0B = duty;
}


static void setPwmDutyChannelA(uint8_t duty){
	DEBUGMESSAGE("SetTim0ChA:%d",duty);
	OCR0A = duty;
}


void setPwmFrequencyTimer0(uint32_t fq){
	uint32_t presc= ((uint32_t)F_CPU)/(fq*510);
	DEBUGMESSAGE("Calc Prescaler:%d\n",presc);
	TCCR0B = 0;
	if(presc > 1024){
		TCCR0B |= (1<<CS02) | (1<<CS01) | (1<< CS00);
	} else if(presc < 1024 && presc > 256){
		TCCR0B |= (1<<CS02) | (1<<CS01);
	} else if(presc < 256 && presc > 128){
		TCCR0B |= (1<<CS02) | (1<< CS00);
	} else if(presc < 128 && presc > 64){
		TCCR0B |= (1<<CS02);
	} else if(presc < 64 && presc > 32){
		TCCR0B |= (1<<CS01) | (1<< CS00);
	} else if(presc < 32 && presc > 8){
		TCCR0B |= (1<<CS01);
	}else {
		TCCR0B |= (1<<CS00);
	}
	//TCCR0B |= (1<<WGM02);
	return;
}


void setPwmTimer0PercDutyChannelB(uint8_t duty){
	uint16_t calcval = (duty*25)/10;
	setPwmDutyChannelB((uint8_t)calcval);
}


void setPwmTimer0PercDutyChannelA(uint8_t duty){
	uint16_t calcval = (duty*25)/10;
	setPwmDutyChannelA((uint8_t)calcval);
}


//for future Use
ISR(TIMER0_COMPA_vect){

}


ISR(TIMER0_COMPB_vect){

}


ISR(TIMER0_OVF_vect){
	
}


