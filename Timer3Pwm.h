


#ifndef TIMER3_H_
#define TIMER3_H_
#include <stdint.h>

void initTimer3ToPwm(void);
void setPwmFrequencyTimer3(uint16_t fq);
void setPwmTimer3PercDutyChannelB(uint8_t duty);
void setPwmTimer3PercDutyChannelA(uint8_t duty);

#endif