

#ifndef	__LED_H
#define __LED_H
#include "stm32f10x.h"

void LED_Init(void);//��ʼ��
//void led(u8 m);

#define	led_d2  PAout(1)  //���ݶ˿�
#define	led_d3  PEout(14)  //���ݶ˿�

#endif


