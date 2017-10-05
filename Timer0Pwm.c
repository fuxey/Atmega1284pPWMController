





#include "Timer0Pwm.h"



void initTimer0ToPwm(void){
	
	TCCR0A |= (1<<COM0B1) |(1<<COM0A1);
	TCCR0A |= (1<<WGM00); //phase correct pwm 8bit
	OCR1A = 0;
	OCR1B = 0;
	TCCR1B |(1<<CS10)|(1<<WGM02);
}


static void setPwmDutyChannelB(uint8_t duty){
	OCR0B = duty;
}


static void setPwmDutyChannelA(uint8_t duty){
	OCR0A = duty;
}


void setPwmFrequencyTimer0(uint16_t fq){
	uint16_t presc= (F_CPU)/(fq*510);
	TCCR0B = (1<<WGM02);
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
		TCCR0B |(1<<CS00);
	}
	return;
}


void setPwmTimer0PercDutyChannelB(uint8_t duty){
	uint16_t calcval = (duty*25)/10;
	setPwmDutyChannelB(((uint8_t)calcval);
}


void setPwmTimer0PercDutyChannelA(uint8_t duty){
	uint16_t calcval = (duty*25)/10;
	setPwmDutyChannelA(((uint8_t)calcval);
}


//for future Use
ISR(TIMER0_COMPA_vect){

}


ISR(TIMER0_COMPB_vect){

}


ISR(TIMER0_OVF_vect){
	
}


