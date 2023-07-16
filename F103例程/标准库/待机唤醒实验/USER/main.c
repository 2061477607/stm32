#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "wkup.h"
#include "TIM.h"
#include "bsp_adc.h"
uint32_t time = 0;

u8 sign=0;
// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal[NOFCHANEL];
/*****************************************************/
//�����ػ�����PA0
//�����źż���PB2
//�̰��źż���PE3
//X�᣺PA2
//Y�᣺PA1
/*****************************************************/



 int main(void)
 {	 
	float x,y;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	BASIC_TIM_Init();//��ʱ����ʼ��
	Key1_Init();
	Key2_Init();
	delay_ms(30);
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��	
	ADCx_Init();
	WKUP_Init(); //�������ѳ�ʼ��
	while(1)
	{
		LED0=!LED0;
		delay_ms(250);
		ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
		ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
		x=1.66-ADC_ConvertedValueLocal[2];
		y=1.66-ADC_ConvertedValueLocal[1];
		if(x>0)
			printf("X�᣺��     ");
		else
			printf("X�᣺��     ");
		if(y>0)
			printf("Y�᣺ǰ\n");
		else
			printf("Y�᣺��\n");
	}
 }

void EXTI2_IRQHandler(void)
{ 	
    int16_t t1=0;	
	EXTI_ClearITPendingBit(EXTI_Line2); // ���LINE10�ϵ��жϱ�־λ		
	if(KEY1==1)
		t1=TIM6->CNT;
	printf("%d",t1);
	while(KEY1);
	t1=TIM6->CNT-t1;
	printf("       %d\n",t1);
	if(t1>6000)
		if(sign)
		{
			printf("#################################\n");//��Ϣ1�Զ���*************************
			sign=0;
		}
		else
		{
			printf("#################################\n");//��Ϣ2�Զ���*************************
			sign=1;
		}
		
}
void EXTI3_IRQHandler(void)
{ 		    		    				     		    
	if(KEY2==1)
	{	
		delay_ms(10);	
		if(KEY2==1)
		{		  
			printf("**************************************\n");//��Ϣ�Զ���*************************
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line3); 
}
