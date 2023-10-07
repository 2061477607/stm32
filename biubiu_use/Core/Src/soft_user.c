#include "soft_user.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;


__IO uint32_t sysTickCnt;

void delay(uint32_t time)
{
    uint32_t i, m;
    for (i = 0; i < time; i++)
    {
        for (m = 0; m < 21000; m++)
            ;
    }
}
void delay_us(uint32_t time)
{
    uint32_t i, m;
    for (i = 0; i < time; i++)
    {
        for (m = 0; m < 21; m++)
            ;
    }
}
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 100);
    return (ch);
}
void Usart_SendByte(UART_HandleTypeDef *pUSARTx, uint8_t ch)
{
    /* ����һ���ֽڵ�USART */
    HAL_UART_Transmit(pUSARTx, (uint8_t *)&ch, 1, 100);
}
// �����ڷ��ͻ�����������ȫ������ȥ
void Usart_SendAll(Usart_DataTypeDef *usart)
{
    uint8_t value;
    while (RingBuffer_GetByteUsed(usart->sendBuf))
    {
        value = RingBuffer_Pop(usart->sendBuf);
        // printf("Usart_SendAll pop: %d", value);
        Usart_SendByte(usart->pUSARTx, value);
    }
}



void clearArray(uint8_t *array, uint16_t length)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        array[i] = 0;
    }
}

// �ȴ���ʱ���
void SysTick_Wait()
{
    // ��ʱ��ʹ��
    TIM6->CR1 |= TIM_CR1_CEN;
    //	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    // �ȴ�ֱ����ʱ����Ϊ0
    while (sysTickCnt > 0)
        ;
    // ��ʱ��ʧ��
    //	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    TIM6->CR1 &= (uint16_t)~TIM_CR1_CEN;
}

// ��ʱus
void SysTick_DelayUs(__IO uint32_t nTime)
{
    // ����ʱ���ж�Ϊus��
    //    SysTick_Config(SystemCoreClock / 1000000);
    TIM6->PSC = 71;
    sysTickCnt = nTime;
    // �ȴ���ʱ���
    SysTick_Wait();
    // ��������ϵͳ�ж�Ϊms��
    TIM6->PSC = 71999;
    // ��ʱ��ʧ��
    TIM6->CR1 &= (uint16_t)~TIM_CR1_CEN;
}

// ��ʱms
void SysTick_DelayMs(__IO uint32_t nTime)
{
    sysTickCnt = nTime;
    SysTick_Wait();
}

// ��ʱs
void SysTick_DelayS(__IO uint32_t nTime)
{
    SysTick_DelayMs(nTime * 1000);
}

// ���õ���ʱ(������ʽ)
void SysTick_CountdownBegin(__IO uint32_t nTime)
{
    // ��������Ϊ1ms�ж�һ��
    sysTickCnt = nTime;
    // ��ʱ��ʹ��
    TIM6->CR1 |= TIM_CR1_CEN;
}

// ��������ʱ
void SysTick_CountdownCancel(void)
{
    // ������઼�ʱ���ļ���ֵ
    sysTickCnt = 0;
    // systick ��ʱ��ʧ��
    TIM6->CR1 &= (uint16_t)~TIM_CR1_CEN;
}

// �жϵ���ʱ�Ƿ�ʱ
uint8_t SysTick_CountdownIsTimeout(void)
{
    return sysTickCnt == 0;
}

