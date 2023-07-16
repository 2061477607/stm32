#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "sys.h"

#define USE_HORIZONTAL 1  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 128
#endif

#define LCD_SDI GPIO_Pin_15
#define LCD_SCL GPIO_Pin_13
#define LCD_CS  GPIO_Pin_12
#define LCD_SDO GPIO_Pin_14
#define LCD_DC  GPIO_Pin_1
#define LCD_BLK GPIO_Pin_8

//-----------------LCD�˿ڶ���----------------
#define LCD_MOSI_Clr() GPIO_ResetBits(GPIOB,LCD_SDI)//SDI=MOSI
#define LCD_MOSI_Set() GPIO_SetBits(GPIOB,LCD_SDI)

#define LCD_SCLK_Clr() GPIO_ResetBits(GPIOB,LCD_SCL)//SCL=CLK
#define LCD_SCLK_Set() GPIO_SetBits(GPIOB,LCD_SCL)

#define LCD_CS_Clr()   GPIO_ResetBits(GPIOB,LCD_CS)//CS
#define LCD_CS_Set()   GPIO_SetBits(GPIOB,LCD_CS)

#define LCD_DC_Clr()   GPIO_ResetBits(GPIOB,LCD_DC)//DC
#define LCD_DC_Set()   GPIO_SetBits(GPIOB,LCD_DC)

#define LCD_BLK_Clr()  GPIO_ResetBits(GPIOA,LCD_BLK)//BLK
#define LCD_BLK_Set()  GPIO_SetBits(GPIOA,LCD_BLK)

#define ZK_MISO        GPIO_ReadInputDataBit(GPIOB,LCD_SDO)//MISO=SDO  ��ȡ�ֿ���������

#define ZK_CS_Set()    GPIO_ResetBits(GPIOB,LCD_CS)//CS
#define ZK_CS_Clr()    GPIO_SetBits(GPIOB,LCD_CS)




void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(u8 dat);//ģ��SPIʱ��
void LCD_WR_DATA8(u8 dat);//д��һ���ֽ�
void LCD_WR_DATA(u16 dat);//д�������ֽ�
void LCD_WR_REG(u8 dat);//д��һ��ָ��
void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2); //�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif




