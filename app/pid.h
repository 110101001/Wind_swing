/**
  ******************************************************************************
  * @file    pid.h
  * @author  Tang Zhixuan
  * @version V1.0
  * @date    2017/5/13
  ******************************************************************************
  */

#ifndef __PID_H
#define __PID_H
#include "pwm.h"

//����ʽPID�㷨
typedef struct 
{
 float kp;     
 float ki;     
 float kd;
 float ref;
 float now;
 float errNow; //��ǰ�����
 float errOld1;
 float errOld2;
 float doutput;//�����������
 float  output;//�������
}PID_Type;

void set_pid(PID_Type* PID,float kp,float ki,float kd);
void pid_cal(PID_Type* PID);
//float Kalman_Filter1(float Accel,float Gyro);		
//float Kalman_Filter2(float Accel,float Gyro);		

#endif
