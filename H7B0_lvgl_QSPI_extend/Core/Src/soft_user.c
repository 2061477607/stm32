#include "soft_user.h"

extern UART_HandleTypeDef huart1;

void delay(uint32_t time)
{
     uint32_t i, m;
     for (i = 0; i < time; i++)
     {
          for (m = 0; m < 140000; m++)
               ;
     }
}
void delay_us(uint32_t time)
{
     uint32_t i, m;
     for (i = 0; i < time; i++)
     {
          for (m = 0; m < 140; m++)
               ;
     }
}
int fputc(int ch, FILE *f)
{
     HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 100); // 发送单字节数据
     return (ch);
}
void Usart_SendString(uint8_t *str)
{
     unsigned int k = 0;
     do
     {
          HAL_UART_Transmit(&huart1, (uint8_t *)(str + k), 1, 1000);
          k++;
     } while (*(str + k) != '\0');
}
