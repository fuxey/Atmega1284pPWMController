





#ifndef PWM_H_
#define PWM_H_ 

#include <stdint.h>


enum PwmChannel{
	PwmCh0 = 0x00,
	PwmCh1,
	PwmCh2,
	PwmCh3,
	PwmCh4,
	PwmCh5,
	PwmCh6,
	PwmCh7,
};


void initPwmTimer(uint16_t PwmFrequency);
void SetPwmChannelDutyCycle(uint8_t channel,uint8_t dutyCyclePercent);
void SetAllPwmChannelToDutyCycle(uint8_t dutycycle);

#endif
