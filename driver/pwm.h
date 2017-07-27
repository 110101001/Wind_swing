#ifndef _PWM_H_
#define _PWM_H_

#define DUTY_MAX 999

#define DUTY1 (TIM3->CCR1)
#define DUTY2 (TIM3->CCR2)
#define DUTY3 (TIM3->CCR3)
#define DUTY4 (TIM3->CCR4)

void PWM_Configuration(void);
						

#endif
