


#ifndef TIMER0_H_
#define TIMER0_H_
#include <stdint.h>


void initTimer0ToPwm(void);
void setPwmFrequencyTimer0(uint16_t fq);
void setPwmTimer0PercDutyChannelB(uint8_t duty);
void setPwmTimer0PercDutyChannelA(uint8_t duty);

#endif 