

#ifndef TIMER1_H_
#define TIMER1_H_

#include <stdint.h>

void initTimer1ToPwm(void);
void setPwmFrequencyTimer1(uint32_t fq);
void setPwmTimer1PercDutyChannelB(uint8_t duty);
void setPwmTimer1PercDutyChannelA(uint8_t duty);
#endif