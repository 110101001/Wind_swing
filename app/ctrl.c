#include "main.h"

#define L (0.6426)//杆长,单位m
#define H (0.835)//杆底部离地面高度

extern PID_Type* Motor_X;
extern PID_Type* Motor_Y;

extern uint32_t time_count;

//float pitch_now,roll_now,pitch_sum,roll_sum;

extern float roll,pitch,yaw;

float laser_radium;//激光笔半径,单位m
float max_angle_degree,max_angle_radian;//角度制&弧度制
float swing_period;
float omega;//角频率
	
float time=0;//time单位s
void calc_init(float laser_radium)
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

void mode1()//15s内画不小于50cm直线
{
	time+=1/1000;
	calc_init(0.25);//0.25为半径
  set_pid(Motor_X,0.01,0,0);
	set_pid(Motor_Y,0.01,0,0);
	while(1){
		Motor_X->ref=max_angle_radian*cos(omega*(time+=(TIM2->CNT - time_count)/1000000));
		Motor_Y->ref=0;
		Motor_X->now=Roll,Motor_Y->now=Pitch;
		pid_cal(Motor_X);
		pid_cal(Motor_Y);
		Set_Motor(Motor_X->output,Motor_Y->output);
	}
}
void mode2()//30-60cm直线
{
	time+=1/1000;
	calc_init(0.15);//自己改，半径
  set_pid(Motor_X,0,0,0);
	set_pid(Motor_Y,0,0,0);
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
	float phase,line_angle;//phase为初相，弧度制, line_angle也为弧度制
	line_angle>=0?(phase=0):(phase=3.1415926);
	time+=1/1000;
	calc_init(0.15);
  set_pid(Motor_X,0,0,0);
	set_pid(Motor_Y,0,0,0);
	Motor_X->ref=max_angle_radian*cos(omega*(time+=(TIM2->CNT - time_count)/1000000));
	calc_init(0.3*tan(line_angle));
  Motor_Y->ref=max_angle_radian*cos(omega*(time+=(TIM2->CNT - time_count)/1000000)+phase);
	pid_cal(Motor_X);
	pid_cal(Motor_Y);
	Set_Motor(Motor_X->output,Motor_Y->output);
}

//===================干扰，5s内稳定======================
void mode4()
{
	time+=1/1000;
	//calc_init(0.25);
  set_pid(Motor_X,1,0,0);
	set_pid(Motor_Y,1,0,0);
	Motor_X->ref=0;
  Motor_Y->ref=0;
	while(1){
		Motor_X->now=Roll,Motor_Y->now=Pitch;
		pid_cal(Motor_X);
		pid_cal(Motor_Y);
		Set_Motor(Motor_X->output,Motor_Y->output);
		ANO_DT_Send_Status(Roll,Pitch,Yaw,Motor_X->output,Motor_Y->output,0);
	}
}
//===================画圆======================
//半径可设置，相位pi/2
void mode5()
{	
	float radium;//半径
	time+=1/1000;
	calc_init(radium);
  set_pid(Motor_X,0,0,0);
	set_pid(Motor_Y,0,0,0);
	Motor_X->ref=max_angle_radian*cos(omega*(time+=(TIM2->CNT - time_count)/1000000));
  Motor_Y->ref=max_angle_radian*cos(omega*(time+=(TIM2->CNT - time_count)/1000000)+3.1415926/2);
	pid_cal(Motor_X);
	pid_cal(Motor_Y);
	Set_Motor(Motor_X->output,Motor_Y->output);
}
void mode6();
