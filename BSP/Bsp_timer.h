#ifndef BSP_TIMER_H_
#define BSP_TIMER_H_

#include "header.h"

void TIMx_Timer_Init(void);

void delay_100us(uint32_t us);
void delay_ms(uint32_t ms);
void delay_s(uint32_t s);

#endif
