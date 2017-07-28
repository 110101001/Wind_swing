#include "main.h"

extern int mode;

extern float Roll,Pitch,Yaw;  
uint32_t time_count;
//int mode_flag=0,mode_change_flag=0;


extern PID_Type* Motor_X;
extern PID_Type* Motor_Y;

void TIM2_Configuration(void)//TIM2作为系统时钟，CNT寄存器中的为计数开始到现在的微秒数
{
    TIM_TimeBaseInitTypeDef tim;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    tim.TIM_Period = 0xFFFFFFFF;
    tim.TIM_Prescaler = 84 - 1;	 //1M 的时钟  
    tim.TIM_ClockDivision = TIM_CKD_DIV1;	
    tim.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_ARRPreloadConfig(TIM2, ENABLE);	
    TIM_TimeBaseInit(TIM2, &tim);
    TIM_Cmd(TIM2,ENABLE);	
}

void TIM2_IRQHandler(void)										
{
	  if (TIM_GetITStatus(TIM2,TIM_IT_Update)!= RESET) 
		{
			  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
        TIM_ClearFlag(TIM2, TIM_FLAG_Update);
		}
} 
void Delay_us(uint32_t us)										//用TIM2的计数值来做到精确延时
{
    uint32_t now = TIM2->CNT;
    while (TIM2->CNT - now < us);
}

void Delay_ms(uint32_t ms)
{
    while (ms--)
        Delay_us(1000);
}

void TIM5_Configuration(int arr,int psc)//1000-1,84-1,1ms进入一次中断
{
	  NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef tim;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
    tim.TIM_Period = arr;
    tim.TIM_Prescaler = psc;	 //1M 的时钟  
	  tim.TIM_ClockDivision=TIM_CKD_DIV1; 	
	  TIM_TimeBaseInit(TIM5,&tim);
	  TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //允许更新中断
	  TIM_Cmd(TIM5,ENABLE); 
	
		NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
		NVIC_Init(&NVIC_InitStructure);  

    TIM_Cmd(TIM5,ENABLE);	
}

void TIM5_IRQHandler(void)
{
	time_count=TIM2->CNT;
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) 
	{
		MPU6050_Read();
	  MPU6050_Data_Prepare(1/1000.0f+(TIM2->CNT-time_count)/1000000.0f);
  	IMUupdate(0.5f *(1/1000.0f+(TIM2->CNT-time_count)/1000000.0f),mpu6050.Gyro_deg.x, mpu6050.Gyro_deg.y, mpu6050.Gyro_deg.z, //??IMU
						mpu6050.Acc.x, mpu6050.Acc.y, mpu6050.Acc.z,&Roll,&Pitch,&Yaw);
    Motor_X->now=Roll,Motor_Y->now=Pitch;
//				for(int i=0;i<3;i++)
//		{
//			pitch_now= ,roll_now=  ;
//			pitch_sum+=pitch_now,roll_sum+=roll_sum;
//		}
//		pitch_now=pitch_sum/3;
//		roll_now=roll_sum/3;
//		pitch_now = Kalman_Filter1(pitch_now,Axis.GyroY);       //卡尔曼滤波器
//		roll_now  = Kalman_Filter2(roll_now,-Axis.GyroX);       //卡尔曼滤波器		  
//	}
				switch(mode)
		{	
			case 1: mode1(); break;
			case 2: mode2(); break;
			case 3: mode3(); break;
			case 4: mode4(); break;
			case 5: mode5(); break;
			//case 6: mode6(); break;
			default:break;
		}	
	//ANO_DT_Send_Status(Roll,Pitch,Yaw,Motor_X->ref,Motor_Y->ref,0);
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
}
}

