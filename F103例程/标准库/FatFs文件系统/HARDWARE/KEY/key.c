

#include "key.h"




void KEY_Init(void)
{
GPIO_InitTypeDef GPIO_InitStructure;	 //�ṹ�嶨��
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//����GPIOA GPIODʱ��
GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_15;	//IO����
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;		   //���ó���������
GPIO_Init(GPIOA,&GPIO_InitStructure);	           //��ʼ��GPIO

}












