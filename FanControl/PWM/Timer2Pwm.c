






#include "Timer2Pwm.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../Uart/Debugmessage.h"



static void PinConfig(){
	DDRD |= (1<<PORTD6)|(1<<PORTD7);
}


static void setPwmDutyChannelB(uint8_t duty){
	DEBUGMESSAGE("SetTim2ChB:%d",duty);
	OCR2B = duty;
}


static void setPwmDutyChannelA(uint8_t duty){
	DEBUGMESSAGE("SetTim2ChA:%d",duty);
	OCR2A = duty;
}


void setPwmFrequencyTimer2(uint32_t fq){
	uint32_t presc= ((uint32_t)F_CPU)/(fq*510);
	DEBUGMESSAGE("Calc Prescaler:%d\n",presc);
	TCCR2B =0;
	if(presc > 1024){
		TCCR2B |= (1<<CS22) | (1<<CS21) | (1<< CS20);
	} else if(presc < 1024 && presc > 256){
		TCCR2B |= (1<<CS22) | (1<<CS21);
	} else if(presc < 256 && presc > 128){
		TCCR2B |= (1<<CS22) | (1<< CS20);
	} else if(presc < 128 && presc > 64){
		TCCR2B |= (1<<CS22);
	} else if(presc < 64 && presc > 32){
		TCCR2B |= (1<<CS21) | (1<< CS20);
	} else if(presc < 32 && presc > 8){
		TCCR2B |= (1<<CS21);
	}else {
		TCCR2B |=(1<<CS20);
	}
	//TCCR2B |= (1<<WGM22);
	return;
}


void initTimer2ToPwm(void){
	
	TCCR2A = 0;
	TCCR2B = 0;
	TCCR2A |=  (1<<WGM20)|(1<<WGM21);
	TCCR2A |= (1<<COM2B1)|(1<<COM2A1); //toggle on compare match
	
	
	OCR2A = 128;
	OCR2B = 128;
	
	TCCR2B |= (1<<CS20); // no prescaling!
//	TCCR2B |= (1<<WGM22);
	
	//Timer Interrupt generation
	//TIMSK2 |= (1<<OCIE2B);//
	//TIMSK2 |= (1<<OCIE2A);//enable
	PinConfig();
}


void setPwmTimer2PercDutyChannelB(uint8_t duty){
	uint16_t calcval = (duty*25)/10;
	setPwmDutyChannelB((uint8_t)calcval);	
}


void setPwmTimer2PercDutyChannelA(uint8_t duty){
	uint16_t calcval = (duty*25)/10;
	setPwmDutyChannelA((uint8_t)calcval);
}




//for future Use
ISR(TIMER2_COMPA_vect){

}


ISR(TIMER2_COMPB_vect){

}


ISR(TIMER2_OVF_vect){
	
}