#include "main.h"

extern int mode;
extern int mode_flag,mode_change_flag;

int main(){
	All_Init();
	mode_change_flag=1;
	mode=1;
	Delay_ms(3000);
	printf("2/n");
  while(1);  
}


