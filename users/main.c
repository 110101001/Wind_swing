#include "main.h"

extern int mode;
extern int mode_flag,mode_change_flag;

int main(){
	All_Init();
	mode_change_flag=1;
	mode=1;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3); 
	Delay_ms(3000);
  while(1);  
}


