#include "main.h"

#define L (0.6426)//杆长,单位m
#define H (0.835)//杆底部离地面高度

int mode;
int mode_flag,mode_change_flag;
extern float Roll,Pitch,Yaw;    				//???


extern PID_Type* Motor_X;
extern PID_Type* Motor_Y;

extern uint32_t time_count;

double laser_radium;//激光笔半径,单位m
double max_angle_degree,max_angle_radian;//角度制&弧度制
double swing_period;
double omega;//角频率
	
double time=0;//time单位s
void calc_init(double laser_radium)
{
	omega=sqrt(9.6949/L);
	max_angle_radian=atan(laser_radium/H);
  max_angle_degree=360*max_angle_radian/(2*3.1415926);
	swing_period=2*3.1415926*sqrt(L/9.6949)*(1+0.25*pow(sin(max_angle_radian/2),2)+0.140625*pow(sin(max_angle_radian/2),4));
  //target_angle=max_angle_radian*cos(omega*time+phase);
}


//float clac_v(float alpha)//用能量守恒;alpha是弧度制;返回当前速度；当前速度就是ref值
//{
//	return(sqrt(2*L*9.6949*(cos(max_angle_radian)-cos(alpha))));
//}

void mode_switch(int mode)
{

}

void mode1()//15s内画不小于50cm直线
{
	if(mode_change_flag==1)
	{
		Delay_ms(5000);//使风力摆稳定下来
		time=0;
	  calc_init(LASER_RADIUM_1);//0.25为半径
    set_pid(Motor_X,20,0,0);
	  set_pid(Motor_Y,20,0,0);
	  mode_change_flag=0;
	}
	  time+=(1/1000+(TIM2->CNT - time_count)/1000000);
		Motor_X->ref=max_angle_radian*cos(omega*time);
		Motor_Y->ref=0;
		pid_cal(Motor_X);
		pid_cal(Motor_Y);
		Set_Motor(Motor_X->output,Motor_Y->output);
}
void mode2()//30-60cm直线
{
		if(mode_change_flag==1)
	{
		Delay_ms(5000);
		time=0;
	  calc_init(LASER_RADIUM_2);//0.25为半径
    set_pid(Motor_X,0,0,0);
	  set_pid(Motor_Y,0,0,0);
	  mode_change_flag=0;
	}
	time+=(1/1000+(TIM2->CNT - time_count)/1000000);
	Motor_X->ref=max_angle_radian*cos(omega*(time+=(TIM2->CNT - time_count)/1000000));
  Motor_Y->ref=0;
	pid_cal(Motor_X);
	pid_cal(Motor_Y);
	Set_Motor(Motor_X->output,Motor_Y->output);
}

//====================================================
//功能：角度可变，长度不小于20cm
//x=A1cos(theta+phase1),y=A22cos(theta+phase2)
//当phase2-phase1=2k*pi（取0） ，y=A2/A1x
//phase2-phase1=pi, y=-A2/A1
//====================================================
void mode3()//设置角度(弧度制)，不小于20cm
{
	float phase,line_angle,Ax;//phase为初相，弧度制, line_angle也为弧度制
	line_angle>=0?(phase=0):(phase=3.1415926);
		if(mode_change_flag==1)
	{
		Delay_ms(5000);
		time=0;
	  calc_init(LASER_RADIUM_3);//0.25为半径
		Ax=max_angle_radian;
		calc_init(0.3*tan(line_angle));
    set_pid(Motor_X,0,0,0);
	  set_pid(Motor_Y,0,0,0);
	  mode_change_flag=0;
	}
	time+=(1/1000+(TIM2->CNT - time_count)/1000000);
	Motor_X->ref=Ax*cos(omega*(time+=(TIM2->CNT - time_count)/1000000));
  Motor_Y->ref=max_angle_radian*cos(omega*(time+=(TIM2->CNT - time_count)/1000000)+phase);
	pid_cal(Motor_X);
	pid_cal(Motor_Y);
	Set_Motor(Motor_X->output,Motor_Y->output);
}

//===================干扰，5s内稳定======================
void mode4()
{
		if(mode_change_flag==1)
	{
		Delay_ms(5000);//使风力摆稳定下来
		time=0;
    set_pid(Motor_X,0,0,0);
	  set_pid(Motor_Y,0,0,0);
	  mode_change_flag=0;
	}
	time+=(1/1000+(TIM2->CNT - time_count)/1000000);
	Motor_X->ref=0;
  Motor_Y->ref=0;
		pid_cal(Motor_X);
		pid_cal(Motor_Y);
		Set_Motor(Motor_X->output,Motor_Y->output);
		ANO_DT_Send_Status(Roll,Pitch,Yaw,Motor_X->output,Motor_Y->output,0);
}
//===================画圆======================
//半径可设置，相位pi/2
//
void mode5()
{		
	if(mode_change_flag==1)
	{
		Delay_ms(5000);//使风力摆稳定下来
		time=0;
	  calc_init(LASER_RADIUM_5);//0.25为半径
    set_pid(Motor_X,0,0,0);
	  set_pid(Motor_Y,0,0,0);
	  mode_change_flag=0;
	}
	time+=1/1000;
	Motor_X->ref=max_angle_radian*cos(omega*(time+=(TIM2->CNT - time_count)/1000000));
  Motor_Y->ref=max_angle_radian*cos(omega*(time+=(TIM2->CNT - time_count)/1000000)+3.1415926/2);
	pid_cal(Motor_X);
	pid_cal(Motor_Y);
	Set_Motor(Motor_X->output,Motor_Y->output);
}

//void mode6();
