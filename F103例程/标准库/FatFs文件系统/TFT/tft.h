
#ifndef __TFT_H
#define __TFT_H
#include "stm32f10x.h"


//����IO
//�ö�����ҪӦ���� ��ʾ  
//����IO����ʾ������ û���κ��������� ֱ�ӵ���IO��ײ�Ĵ�������
//�Դﵽ ��MCU������Χ�ڵ������ʾЧ��
#define	TFT_CS_1    GPIOE->BSRR=1<<0     //Ƭѡ�˿�  	     PE0
#define	TFT_RS_1	GPIOC->BSRR=1<<4     //����/����         PC4	   
#define	TFT_WR_1	GPIOC->BSRR=1<<2    //д����			 PC2
#define	TFT_RD_1	GPIOC->BSRR=1<<0    //������			 PC0
								    
#define	TFT_CS_0    GPIOE->BRR=1<<0      //Ƭѡ�˿�  	     PE0
#define	TFT_RS_0	GPIOC->BRR=1<<4      //����/����         PC4	   
#define	TFT_WR_0	GPIOC->BRR=1<<2     //д����			 PC2
#define	TFT_RD_0	GPIOC->BRR=1<<0     //������			 PC0



void TFT_CS(u8 d);

void Lcd_Init(void);


void Lcd_Write_Data(u16 data);								 //д16λ����

void Address_set(u16 x1,u16 y1,u16 x2,u16 y2,u16 xq,u16 yq);    //������ʾ��Χ




//��Ļ�ߴ�
#define TFT_XMAX       239
#define TFT_YMAX       319




#endif






