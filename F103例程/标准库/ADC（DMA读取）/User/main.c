
// ADC 6通道采集实验

#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"

// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal[NOFCHANEL];        

// 软件延时
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{		
	// 配置串口
	USART_Config();
	
	// ADC 初始化
	ADCx_Init();
	
	printf("\r\n ----这是一个ADC多通道采集实验----\r\n");
	
	while (1)
	{	
    
			//ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
			ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
			ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
			//ADC_ConvertedValueLocal[3] =(float) ADC_ConvertedValue[3]/4096*3.3;
			//ADC_ConvertedValueLocal[4] =(float) ADC_ConvertedValue[4]/4096*3.3;
			//ADC_ConvertedValueLocal[5] =(float) ADC_ConvertedValue[5]/4096*3.3;
		
			printf("\n CH2 value = %.2f V \n",1.66-ADC_ConvertedValueLocal[2]);
			printf("\n CH1 value = %.2f V \n",1.66-ADC_ConvertedValueLocal[1]);
			//printf("\n CH2 value = %f V \n",ADC_ConvertedValueLocal[2]);
			//printf("\n CH3 value = %f V \n",ADC_ConvertedValueLocal[3]);
			//printf("\n CH4 value = %f V \n",ADC_ConvertedValueLocal[4]);
			//printf("\n CH5 value = %.2f V \n",ADC_ConvertedValueLocal[5]);
		
			printf("\n\n");
			Delay(0xffff1);		 
	}
}
/*********************************************END OF FILE**********************/

