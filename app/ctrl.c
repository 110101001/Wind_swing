#include "main.h"

#define L (0.6426)//�˳�,��λm
#define H (0.835)//�˵ײ������߶�

int mode;
int mode_flag,mode_change_flag;
extern float Roll,Pitch,Yaw;    				//???


extern PID_Type* Motor_X;
extern PID_Type* Motor_Y;

extern uint32_t time_count;

double laser_radium;//����ʰ뾶,��λm
double max_angle_degree,max_angle_radian;//�Ƕ���&������
double swing_period;
double omega;//��Ƶ��
	
double time=0;//time��λs
void calc_init(double laser_radium)
{
	omega=sqrt(9.6949/L);
	max_angle_radian=atan(laser_radium/H);
  max_angle_degree=360*max_angle_radian/(2*3.1415926);
	swing_period=2*3.1415926*sqrt(L/9.6949)*(1+0.25*pow(sin(max_angle_radian/2),2)+0.140625*pow(sin(max_angle_radian/2),4));
  //target_angle=max_angle_radian*cos(omega*time+phase);
}


//float clac_v(float alpha)//�������غ�;alpha�ǻ�����;���ص�ǰ�ٶȣ���ǰ�ٶȾ���refֵ
//{
//	return(sqrt(2*L*9.6949*(cos(max_angle_radian)-cos(alpha))));
//}

void mode_switch(int mode)
{

}

void mode1()//15s�ڻ���С��50cmֱ��
{
	if(mode_change_flag==1)
	{
		Delay_ms(5000);//ʹ�������ȶ�����
		time=0;
	  calc_init(LASER_RADIUM_1);//0.25Ϊ�뾶
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
void mode2()//30-60cmֱ��
{
		if(mode_change_flag==1)
	{
		Delay_ms(5000);
		time=0;
	  calc_init(LASER_RADIUM_2);//0.25Ϊ�뾶
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
//���ܣ��Ƕȿɱ䣬���Ȳ�С��20cm
//x=A1cos(theta+phase1),y=A22cos(theta+phase2)
//��phase2-phase1=2k*pi��ȡ0�� ��y=A2/A1x
//phase2-phase1=pi, y=-A2/A1
//====================================================
void mode3()//���ýǶ�(������)����С��20cm
{
	float phase,line_angle,Ax;//phaseΪ���࣬������, line_angleҲΪ������
	line_angle>=0?(phase=0):(phase=3.1415926);
		if(mode_change_flag==1)
	{
		Delay_ms(5000);
		time=0;
	  calc_init(LASER_RADIUM_3);//0.25Ϊ�뾶
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

//===================���ţ�5s���ȶ�======================
void mode4()
{
		if(mode_change_flag==1)
	{
		Delay_ms(5000);//ʹ�������ȶ�����
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
//===================��Բ======================
//�뾶�����ã���λpi/2
//
void mode5()
{		
	if(mode_change_flag==1)
	{
		Delay_ms(5000);//ʹ�������ȶ�����
		time=0;
	  calc_init(LASER_RADIUM_5);//0.25Ϊ�뾶
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
