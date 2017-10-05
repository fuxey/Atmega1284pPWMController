


#ifndef TIMER2_H_
#define TIMER2_H_



#include <stdint.h>

void initTimer2ToPwm(void);
void setPwmFrequencyTimer2(uint32_t fq);
void setPwmTimer2PercDutyChannelB(uint8_t duty);
void setPwmTimer2PercDutyChannelA(uint8_t duty);
#endif