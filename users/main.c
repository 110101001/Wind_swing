#include "main.h"

int main(){
	All_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);   
	Set_Motor(0,0);
	//while(1);
	mode4();
	while(1){
		if (appTosave)											//��ѭ�����ж��Ƿ�Ҫ������ֲ���
		{
			appTosave=0;
	//		AppParamSave();										//����������ĺ�������main������
		}			
															//��Ϊ��дflashʱ�������жϺ���������ִ��
		
	//	Delay_ms(50);
	}
}


