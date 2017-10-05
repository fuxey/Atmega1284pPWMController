


#include "Timer1Pwm.h"


void initTimer1ToPwm(void){
	
	TCCR1A |= (1<<COM1B1) |(1<<COM1A1);
	TCCR1A |= (1<<WGM10); //phase correct pwm 8bit
	OCR1A = 0;
	OCR1B = 0;
	TCCR1B |(1<<CS10);
}


static void setPwmDutyChannelB(uint8_t duty){
	OCR1B = duty;
}


static void setPwmDutyChannelA(uint8_t duty){
	OCR1A = duty;
}


void setPwmFrequencyTimer1(uint16_t fq){
	uint16_t presc= (F_CPU)/(fq*510);
	TCCR1B = 0;
	if(presc > 1024){
		TCCR1B |= (1<<CS12) | (1<<CS11) | (1<< CS10);
	} else if(presc < 1024 && presc > 256){
		TCCR1B |= (1<<CS12) | (1<<CS11);
	} else if(presc < 256 && presc > 128){
		TCCR1B |= (1<<CS12) | (1<< CS10);
	} else if(presc < 128 && presc > 64){
		TCCR1B |= (1<<CS12);
	} else if(presc < 64 && presc > 32){
		TCCR1B |= (1<<CS11) | (1<< CS10);
	} else if(presc < 32 && presc > 8){
		TCCR1B |= (1<<CS11);
	}else {
		TCCR1B |(1<<CS10);
	}
	return;
}


void setPwmTimer1PercDutyChannelB(uint8_t duty){
	uint16_t calcval = (duty*25)/10;
	setPwmDutyChannelB(((uint8_t)calcval);
}


void setPwmTimer1PercDutyChannelA(uint8_t duty){
	uint16_t calcval = (duty*25)/10;
	setPwmDutyChannelA(((uint8_t)calcval);
}


//for future Use
ISR(TIMER1_COMPA_vect){

}


ISR(TIMER1_COMPB_vect){

}


ISR(TIMER1_OVF_vect){
	
}