#include "hc_sr04.h"
void chaoshengbo_Config(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
 	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	 //ʹ��RCCʱ��

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		GPIO_Init(GPIOB, &GPIO_InitStructure);					 //��ʼ�����
	    GPIO_ResetBits(GPIOB,GPIO_Pin_14);
}

void Trig_Config(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	
	SysTick_Delay_Us(20);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
}

