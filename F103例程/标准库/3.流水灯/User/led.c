#include "led.h"

void LED_Init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
 	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	 //ʹ��RCCʱ��

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		GPIO_Init(GPIOA, &GPIO_InitStructure);					 //��ʼ�����
		
		GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);// ����ߵ�ƽ
}
void delay_ms(u16 time)

{

u16 i=0;

while(time--)

{

i=1000;  

while(i--) ;

}

}
void LED_Light(void)
{

	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	delay_ms(1000);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	delay_ms(1000);
  GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	delay_ms(1000);
  GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	delay_ms(1000);
  GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	delay_ms(1000);
  GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	delay_ms(1000);
  GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	GPIO_SetBits(GPIOA,GPIO_Pin_6);
	delay_ms(1000);
  GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);
	delay_ms(1000);
  GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	
}


