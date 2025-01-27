#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "sys.h"

#define USE_HORIZONTAL 1  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏


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
#define LCD_DC  GPIO_Pin_6
#define LCD_BLK GPIO_Pin_7

//-----------------LCD端口定义----------------
#define LCD_MOSI_Clr() GPIO_ResetBits(GPIOB,LCD_SDI)//SDI=MOSI
#define LCD_MOSI_Set() GPIO_SetBits(GPIOB,LCD_SDI)

#define LCD_SCLK_Clr() GPIO_ResetBits(GPIOB,LCD_SCL)//SCL=CLK
#define LCD_SCLK_Set() GPIO_SetBits(GPIOB,LCD_SCL)

#define LCD_CS_Clr()   GPIO_ResetBits(GPIOB,LCD_CS)//CS
#define LCD_CS_Set()   GPIO_SetBits(GPIOB,LCD_CS)

#define LCD_DC_Clr()   GPIO_ResetBits(GPIOC,LCD_DC)//DC
#define LCD_DC_Set()   GPIO_SetBits(GPIOC,LCD_DC)

#define LCD_BLK_Clr()  GPIO_ResetBits(GPIOC,LCD_BLK)//BLK
#define LCD_BLK_Set()  GPIO_SetBits(GPIOC,LCD_BLK)

#define ZK_MISO        GPIO_ReadInputDataBit(GPIOB,LCD_SDO)//MISO=SDO  读取字库数据引脚

#define ZK_CS_Set()    GPIO_ResetBits(GPIOB,LCD_CS)//CS
#define ZK_CS_Clr()    GPIO_SetBits(GPIOB,LCD_CS)




void LCD_GPIO_Init(void);//初始化GPIO
void LCD_Writ_Bus(u8 dat);//模拟SPI时序
void LCD_WR_DATA8(u8 dat);//写入一个字节
void LCD_WR_DATA(u16 dat);//写入两个字节
void LCD_WR_REG(u8 dat);//写入一个指令
void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2); //设置坐标函数
void LCD_Init(void);//LCD初始化
#endif




