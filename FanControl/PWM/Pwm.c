
#include "Pwm.h"
#include "Timer0Pwm.h"
#include "Timer1Pwm.h"
#include "Timer2Pwm.h"
#include "Timer3Pwm.h"


void initPwmTimer(uint32_t PwmFrequency){
	initTimer0ToPwm();
	initTimer1ToPwm();
	initTimer2ToPwm();
	initTimer3ToPwm();
	
	setPwmFrequencyTimer0(PwmFrequency);
	setPwmFrequencyTimer1(PwmFrequency);
	setPwmFrequencyTimer2(PwmFrequency);
	setPwmFrequencyTimer3(PwmFrequency);
}


void SetPwmChannelDutyCycle(uint8_t channel,uint8_t dutyCyclePercent){
	if(dutyCyclePercent >= 100){
		dutyCyclePercent = 100;
	}
	switch(channel){
		case PwmCh0: setPwmTimer0PercDutyChannelA(dutyCyclePercent); break;
		case PwmCh1: setPwmTimer0PercDutyChannelB(dutyCyclePercent); break;
		case PwmCh2: setPwmTimer1PercDutyChannelA(dutyCyclePercent); break;
		case PwmCh3: setPwmTimer1PercDutyChannelB(dutyCyclePercent); break;
		case PwmCh4: setPwmTimer2PercDutyChannelA(dutyCyclePercent); break;
		case PwmCh5: setPwmTimer2PercDutyChannelB(dutyCyclePercent); break;
		case PwmCh6: setPwmTimer3PercDutyChannelA(dutyCyclePercent); break;
		case PwmCh7: setPwmTimer3PercDutyChannelB(dutyCyclePercent); break;
		default: break;
	}
}


void SetAllPwmChannelToDutyCycle(uint8_t dutycycle){
	setPwmTimer0PercDutyChannelA(dutycycle);
	setPwmTimer0PercDutyChannelB(dutycycle);	

	setPwmTimer1PercDutyChannelA(dutycycle);
	setPwmTimer1PercDutyChannelB(dutycycle);

	setPwmTimer2PercDutyChannelA(dutycycle);
	setPwmTimer2PercDutyChannelB(dutycycle);

	setPwmTimer3PercDutyChannelA(dutycycle);
	setPwmTimer3PercDutyChannelB(dutycycle);
}
