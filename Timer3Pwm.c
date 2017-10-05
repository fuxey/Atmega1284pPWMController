





#include "Timer3Pwm.h"



void initTimer3ToPwm(void){
	
	TCCR3A |= (1<<COM3B1) |(1<<COM3A1);
	TCCR3A |= (1<<WGM30); //phase correct pwm 8bit
	OCR3A = 0;
	OCR3B = 0;
	TCCR3B |(1<<CS30);
}


static void setPwmDutyChannelB(uint8_t duty){
	OCR3B = duty;
}


static void setPwmDutyChannelA(uint8_t duty){
	OCR3A = duty;
}


void setPwmFrequencyTimer3(uint16_t fq){
	uint16_t presc= (F_CPU)/(fq*510);
	TCCR3B =0;
	if(presc > 1024){
		TCCR3B |= (1<<CS32) | (1<<CS31) | (1<< CS30);
	} else if(presc < 1024 && presc > 256){
		TCCR3B |= (1<<CS32) | (1<<CS31);
	} else if(presc < 256 && presc > 128){
		TCCR3B |= (1<<CS32) | (1<< CS30);
	} else if(presc < 128 && presc > 64){
		TCCR3B |= (1<<CS12);
	} else if(presc < 64 && presc > 32){
		TCCR3B |= (1<<CS31) | (1<< CS30);
	} else if(presc < 32 && presc > 8){
		TCCR3B |= (1<<CS31);
	}else {
		TCCR3B |(1<<CS30);
	}
	return;
}


void setPwmTimer3PercDutyChannelB(uint8_t duty){
	uint16_t calcval = (duty*25)/10;
	setPwmDutyChannelB(((uint8_t)calcval);
}


void setPwmTimer3PercDutyChannelA(uint8_t duty){
	uint16_t calcval = (duty*25)/10;
	setPwmDutyChannelA(((uint8_t)calcval);
}


//for future Use
ISR(TIMER3_COMPA_vect){

}


ISR(TIMER3_COMPB_vect){

}


ISR(TIMER3_OVF_vect){
	
}