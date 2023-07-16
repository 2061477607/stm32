#include "spi.h"
#include "delay.h"

static void SPI__BLK(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��A�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = SPI_BLK;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  //��ʼ��GPIOA
 	GPIO_SetBits(GPIOA,SPI_BLK);
}
void SPI_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(SPI_RCC_APB2Periph_GPIO, ENABLE);	 //ʹ��A�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = SPI_SCL|SPI_SDA|SPI_RES|SPI_DC|SPI_CS;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	GPIO_Init(SPI_GPIO, &GPIO_InitStructure);	  //��ʼ��GPIOA
 	GPIO_SetBits(SPI_GPIO,SPI_SCL|SPI_SDA|SPI_RES|SPI_DC|SPI_CS);
	SPI__BLK();
}



/******************************************************************************
      ����˵����SPI��������д�뺯��
      ������ݣ�dat  Ҫд��Ĵ�������
      ����ֵ��  ��
******************************************************************************/
void SPI_Writ_Bus(u8 dat) 
{	
	u8 i;
	SPI_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		SPI_SCLK_Clr();
		if(dat&0x80)
		{
		   SPI_MOSI_Set();
		}
		else
		{
		   SPI_MOSI_Clr();
		}
		SPI_SCLK_Set();
		dat<<=1;
	}	
  SPI_CS_Set();	
}


/******************************************************************************
      ����˵����SPIд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void SPI_WR_DATA8(u8 dat)
{
	SPI_Writ_Bus(dat);
}


/******************************************************************************
      ����˵����SPIд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void SPI_WR_DATA(u16 dat)
{
	SPI_Writ_Bus(dat>>8);
	SPI_Writ_Bus(dat);
}


/******************************************************************************
      ����˵����SPIд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void SPI_WR_REG(u8 dat)
{
	SPI_DC_Clr();//д����
	SPI_Writ_Bus(dat);
	SPI_DC_Set();//д����
}










