#include"stm32f10x.h"

int main(void)
{
  *(unsigned int *)0x40021018 |= ((1)<<4);//��ʱ�ӡ�
	
  *(unsigned int *)0x40011004 |= ((1)<<(20));//PC13���ڸ߼Ĵ������ڹٷ��ֲ����ҵ�Ϊ20.
	
	*(unsigned int *)0x4001100C &=~(1<<13);//��ʼ��ַ+ƫ�ƣ�ʹPC13�˿ڵ͵硣
   return 0;
}
void SystemInit(void)
{}


