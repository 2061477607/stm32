

#include "led.h"



void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;					 //����GPIO�ṹ��
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE);	//ʹ��PC�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			 //�˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��
 GPIO_SetBits(GPIOA,GPIO_Pin_1);						 //�����


 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;			 //LED�˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIO
 GPIO_SetBits(GPIOE,GPIO_Pin_14);						 //�����


}
 
