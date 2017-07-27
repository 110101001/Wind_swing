#ifndef __CTRL_H
#define __CTRL_H

void calc_init(float laser_radium);

void mode1(void);//15s内画不小于50cm直线
void mode2(void);//30-60cm直线
void mode3(void);//设置角度，不小于20cm
void mode4(void);
void mode5(void);
void mode6(void);


#endif
