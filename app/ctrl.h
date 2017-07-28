#ifndef __CTRL_H
#define __CTRL_H

#define LASER_RADIUM_1 0.25
#define LASER_RADIUM_2 0.15
#define LASER_RADIUM_3 0.15
#define LASER_RADIUM_5 0.15
#define LASER_RADIUM_6

void calc_init(double laser_radium);

void mode1(void);//15s内画不小于50cm直线
void mode2(void);//30-60cm直线
void mode3(void);//设置角度，不小于20cm
void mode4(void);
void mode5(void);
void mode6(void);

void mode_switch(int mode);
void ctrl_init(void);

#endif
