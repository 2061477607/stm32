#include "delay.h"
#include "sys.h"
#include "led.h"
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"
#include "pwm2.h"
#include "adc.h"
#include <math.h>
#include <string.h>
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal[NOFCHANEL];
int main(void)
{
	int l,m;char str[10];
	delay_init();
	ADCx_Init();
	LED_Init();//LED��ʼ��
	LCD_Init();//LCD��ʼ��
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
	LED=0;
	TIM2_PWM_Init(7200,100);TIM_SetCompare2(TIM2,4600);
	LCD_DrawLine(14,8,14,108,BLACK);//��ָ��λ�û�һ����	y��
	LCD_DrawLine(14,108,154,108,BLACK);//��ָ��λ�û�һ����	x��
	LCD_ShowChar(3,4,'y',RED,WHITE,16,1);//��ʾһ���ַ�
	LCD_ShowChar(3,15,'/',RED,WHITE,16,1);//��ʾһ���ַ�
	LCD_ShowChar(3,24,'v',RED,WHITE,16,1);//��ʾһ���ַ�
	LCD_ShowChar(3,32,'c',RED,WHITE,16,1);//��ʾһ���ַ�
	LCD_ShowChar(3,40,'c',RED,WHITE,16,1);//��ʾһ���ַ�
	LCD_ShowString(154-32,128-19,"x/ms",RED,WHITE,16,0);//��ʾ�ַ���
	while(1)
	{
		for(l=0;l<140;l++)
		{
			ADC_ConvertedValueLocal[0] =(float)ADC_ConvertedValue[0]/4096*3.3;
			m=(int)(ADC_ConvertedValueLocal[0]*20)+1;
			LCD_DrawPoint(15+l,90-m,BLACK);			
		}
		sprintf(str,"v:%.2f",(float)ADC_ConvertedValue[0]/4096*3.3);
		LCD_ShowString(50,128-19,str,RED,WHITE,16,0);//��ʾ�ַ���
		delay_ms(1000);
		LCD_Fill(15,7,155,107,LGRAY);//ָ�����������ɫ
	}
}

