#ifndef _TIMER_H_
#define _TIMER_H_
#include "stm32f4xx.h"

void TIM2_Configuration(void);
void TIM5_Configuration(int arr,int psc);
void Delay_us(uint32_t us);		//用TIM2的计数值来做到精确延时
void Delay_ms(uint32_t ms);


#endif
