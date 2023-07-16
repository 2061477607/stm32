#include "stm32f10x.h"
#include "LED.h"
#include "systick.h"
#include "iic_gpio.h"
#include "iic_oled.h"
#include <string.h>
#include <stdio.h>
extern const unsigned char BMP1[];
unsigned  char cStr [10]; //ds18b20
float num;
int main(void)
{
	unsigned char i;
	num=15.28;
	OLED_Init();
	LED_GPIO_Config();
	LED1(0);
	OLED_Fill(0xFF);Delay_ms(1000);
	OLED_Fill(0x00);//ȫ����
	Delay_ms(1000);
	for(i=0;i<4;i++)
		{
			OLED_ShowCN(32+i*16,0,i);									//������ʾ����
		}
   while(1)
	 {
//	 OLED_Fill(0xFF);//ȫ������
//	Delay_ms(1000);		// 2s
//	
	//OLED_Fill(0x00);//ȫ����
//	Delay_ms(1000);		// 2s
		 
		
		sprintf ( (char*)cStr, "Pitch:%0.3f",num);
		OLED_ShowStr(0,3,cStr,1);				//��ʾ���ֱ���
		sprintf ( (char*)cStr, "Distance:%0.3f",num);
		OLED_ShowStr(0,5,cStr,1);
		sprintf ( (char*)cStr, "VVV:%0.3f",num);
		OLED_ShowStr(0,7,cStr,1);
//		OLED_ShowStr(0,5,(unsigned char*)"Hello wildfire",2);				//����8*16�ַ�
//		Delay_ms(2000);		// 2*100=200s
//		OLED_CLS();//����
//		OLED_OFF();//����OLED����
//		Delay_ms(1000);		// 2s
//		OLED_ON();//����OLED���ߺ���
//		OLED_DrawBMP(0,0,128,8,(unsigned char *)BMP1);//����BMPλͼ��ʾ
		Delay_ms(2000);		// 2s
  }
}
