#include "stm32f10x.h"  
#include "LED.h"
#include "bsp_usart_dma.h"

extern uint8_t SendBuff[SENDBUFF_SIZE];
static void Delay(__IO u32 nCount); 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  uint16_t i;
  /* ��ʼ��USART */
  USART_Config(); 

  /* ����ʹ��DMAģʽ */
  USARTx_DMA_Config();

  LED_Init();

  
  
  /*��佫Ҫ���͵�����*/
  for(i=0;i<SENDBUFF_SIZE;i++)
  {
    SendBuff[i]	 = 'w';
  
  }

  
  USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx, ENABLE);

  while(1)
  {
    TOGGLE
    Delay(0xFFFFF);
  }
}

static void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}


