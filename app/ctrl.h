#ifndef __CTRL_H
#define __CTRL_H

#define LASER_RADIUM_1 0.25
#define LASER_RADIUM_2 0.15
#define LASER_RADIUM_3 0.15
#define LASER_RADIUM_5 0.15
#define LASER_RADIUM_6

void calc_init(double laser_radium);

void mode1(void);//15s�ڻ���С��50cmֱ��
void mode2(void);//30-60cmֱ��
void mode3(void);//���ýǶȣ���С��20cm
void mode4(void);
void mode5(void);
void mode6(void);

void mode_switch(int mode);
void ctrl_init(void);

#endif
