#ifndef _TIMER_H_
#define _TIMER_H_
#include "stm32f4xx.h"

void TIM2_Configuration(void);
void TIM5_Configuration(int arr,int psc);
void Delay_us(uint32_t us);		//��TIM2�ļ���ֵ��������ȷ��ʱ
void Delay_ms(uint32_t ms);


#endif
