#include "car.h"

void M_Init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
 	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	 //ʹ��RCCʱ��

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		GPIO_Init(GPIOA, &GPIO_InitStructure);					 //��ʼ�����
		
}
//  4 2  -
//  3 1  +
void car_left(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	
}
void car_right(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}
void car_back(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_3);
}
void car_go(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_3);
	
}
void car_stop(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2);
}

