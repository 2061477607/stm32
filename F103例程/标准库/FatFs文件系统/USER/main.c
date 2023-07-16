/*
SDIOģʽ�������屳���TF����   �������ӵķ�ʽ�� SDIOģʽ
SDIO�ӿڶ���   
SDIO_D0  PC8
SDIO_D1  PC9
SDIO_D2  PC10
SDIO_D3  PC11
SDIO_SCK PC12
SDIO_CMD PD2
*/
#include "iic_oled.h"
#include "iic_gpio.h"
#include  "stm32f10x.h"
#include  "delay.h"
#include  "led.h"
#include  "sdio_sdcard.h" 
#include  "pff.h"				  //�ļ�ϵͳ����.h����
#include <stdio.h>
#include <string.h>
#include  "usart.h"
FATFS fatfs;	//�ļ�ϵͳ�ṹ�嶨��

int tbuf[512];			   //512�ֽ� SD�����ݻ���ռ�


//��ʾBIN�ļ�  bin�ļ���СΪ240x320
//path  bin�ļ���
//����0 ��ʾ��� 1  ��ȡʧ��
u8 play_bin(const char  *path)
{

FRESULT res; 
u16 br;
	
res=pf_open(path);		             //��ָ��·���ļ�	 ��һ�����Դ��κ�·���µ��ļ� ע�����Ĺ��ܾ��Ǵ��ļ��������ļ���
                                     //���ļ������ݵ�ǰ���Ǳ���Ҫ������ļ�
  if(res == FR_OK)
	{
		pf_read(tbuf,16,&br);		//���� res=pf_open(path);�򿪵���ָ��·���µ��ļ�������Ϳ���ֱ�Ӷ�ȡ�ļ�������
	                                //�ӳ�ʼλ�ö�ȡ512���ֽڵ�������  �ٴζ�ȡ����ƫ�� �Զ�������512�ֽ�
									//pf_read���ص㣺�������Զ�ȡ·���µ��ļ����ݣ������㲻�ı�·����ǰ�������Զ��ӵ�ַ��ȡ���������
									//�ӳ�����Կ��� �����ڲ�ͣ��ѭ��pf_read(tbuf, 512, &br);��������ȡ512���ֽڣ�
									//��ô���ڲ��Ĺ������ǴӸ���·����ʼ��ȥ512���ֽ�Ȼ���Զ�ָ���512�ֽڵ�·������ȡ��512���ֽ�ֱ��ͼƬ��ʾ���
	    if(tbuf[0]<0)
			;
		else			
		OLED_ShowStr(0,2,(unsigned char*)tbuf,1);
		if(br==0){led_d2;return 0;}   	 //û������ br��Ϊ0  ��ʱ��������	          			
	}

 return 1;  	//˵����ȡ���ݳ�������
 }  	

int main(void)
 {
	  unsigned char str[10];
	  delay_init();	    	 //��ʱ������ʼ��	 	  
      OLED_Init();
      OLED_Fill(0xFF);
	  OLED_Fill(0x00);
	  if(TFsdio_Init()==0)sprintf((char*)str,"TF Card  ok");
	  else{ sprintf((char*)str,"TF Card Error");}
	  OLED_ShowStr(0,0,str,1);
	  delay_ms(500);
	  pf_mount(&fatfs);	         //��ʼ��petit FATFS�ļ�ϵͳ  ����ȡtf����Ӧ����                      
      play_bin("/cat.txt");	       //��ʾָ��·���µ�bin�ļ�	   
                               //����Ҫ��֪����TF�����·�� ��/4.bin��������TF����Ŀ¼���ļ���Ϊ4.bin�ļ�
							  //�����ļ����ļ��� �����ļ����µ�4.bin ��ô��Ҫд"/����/4.bin"
}
	    





