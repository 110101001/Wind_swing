#include "main.h"

extern int mode_change_flag;
extern enum PendulumMode NS;	//NS用于切换模式，Stop为停止模式，Task1到Task6分别为题1至题2

int main(){
	All_Init();
	mode_change_flag=1;
	//NS=Task1;
	Delay_ms(3000);
	
  while(1);  
}


