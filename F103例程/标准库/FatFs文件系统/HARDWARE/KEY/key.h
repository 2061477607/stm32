

#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"

#define S2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)			   //�궨�� Ϊ�ɼ�������׼��
#define S3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)

void KEY_Init(void);//IO��ʼ��



#endif
