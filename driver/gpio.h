#ifndef _GPIO_H_
#define _GPIO_H_

#include "stm32f4xx_gpio.h"
/*
				MOTOR1         PE14
				MOTOR2         PE13
				MOTOR3         PE11
				MOTOR4         PE9
*/

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 

#define IN1 BIT_ADDR(GPIOC_ODR_Addr,12)
#define IN2 BIT_ADDR(GPIOE_ODR_Addr,14)
#define IN3 BIT_ADDR(GPIOD_ODR_Addr,2)
#define IN4 BIT_ADDR(GPIOE_ODR_Addr,13)
#define IN5 BIT_ADDR(GPIOA_ODR_Addr,0)
#define IN6 BIT_ADDR(GPIOE_ODR_Addr,11)
#define IN7 BIT_ADDR(GPIOA_ODR_Addr,1)
#define IN8 BIT_ADDR(GPIOE_ODR_Addr,9)

void GPIO_Configuration(void);

#endif

