#include "main.h"

extern int mode_change_flag;
extern enum PendulumMode NS;	//NS�����л�ģʽ��StopΪֹͣģʽ��Task1��Task6�ֱ�Ϊ��1����2

int main(){
	All_Init();
	mode_change_flag=1;
	//NS=Task1;
	Delay_ms(3000);
	
  while(1);  
}


