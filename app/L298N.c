#include "main.h"

void PWM_M1_Forward(int pwm)
{   	
	DUTY1=pwm;
	IN1=1,IN2=0;
}

void PWM_M2_Forward(int pwm)
{   	
	DUTY2=pwm;
	IN3=1,IN4=0;
}

void PWM_M3_Forward(int pwm)
{   	
	DUTY3=pwm;
	IN5=1,IN6=0;
}

void PWM_M4_Forward(int pwm)
{   	
	DUTY4=pwm;
	IN7=1,IN8=0;
}

void PWM_M1_Backward(int pwm)
{   	
	DUTY1=pwm;
	IN1=0,IN2=1;
}

void PWM_M2_Backward(int pwm)
{   	
	DUTY2=pwm;
	IN3=0,IN4=1;
}

void PWM_M3_Backward(int pwm)
{   	
	DUTY3=pwm;
	IN5=0,IN6=1;
}

void PWM_M4_Backward(int pwm)
{   	
	DUTY4=pwm;
	IN7=0,IN8=1;
}



//void Set_Motor(int pwm1,int pwm2)//x方向，y方向
//{
//	if(pwm1 >= 0)
//	{
//	 	PWM_M2_Forward(pwm1);
//		PWM_M4_Backward(pwm1);
//	}
//	else if(pwm1 < 0)
//	{
//	 	PWM_M2_Backward(-pwm1);
//		PWM_M4_Forward(-pwm1);	
//	}

//	if(pwm2 >= 0)
//	{
//	 	PWM_M1_Forward(pwm2);
//		PWM_M3_Backward(pwm2);
//	}
//	else if(pwm2 < 0)
//	{
//	 	PWM_M1_Backward(-pwm2);
//		PWM_M3_Forward(-pwm2);	
//	} 	
//}

void Set_Motor(int pwm1,int pwm2)//x方向，y方向
{
	if(pwm1 >= 0)
	{
		PWM_M2_Backward(pwm1);
		PWM_M4_Forward(pwm1);
	}
	else if(pwm1 < 0)
	{
		PWM_M4_Backward(pwm1);
		PWM_M2_Forward(pwm1);
	}

	if(pwm2 >= 0)
	{
	 	PWM_M1_Forward(pwm2);
		PWM_M3_Backward(pwm2);
	}
	else if(pwm2 < 0)
	{
	 	PWM_M3_Forward(pwm2);
		PWM_M1_Backward(pwm2);
	} 	
}
