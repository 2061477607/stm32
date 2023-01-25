#ifndef _LCD_LTDC_H_
#define _LCD_LTDC_H_

#include "main.h"
#include "stm32h7xx_hal.h"


// layer0 ���Դ��ַ��������ʹ��7B0�ڲ���AXI SRAM��Ϊ�Դ棬��ʼ��ַ0x24000000����СΪ1M
// layer0 �Դ��С���� = LCD_Width * LCD_Width * BytesPerPixel_0��ÿ��������ռ�ֽڴ�С��
// ��Ϊ AXI SRAM �Ĵ�Сֻ��1M���û����õ�����һ�����ܳ������ֵ��
// �ڱ������У�800*480����Ļ��ʹ��RGB565��ʽ����Ҫ�Դ� 800*480*2 = 768000 �ֽ�
#define LCD_MemoryAdd 0x24000000            //	�Դ����ʼ��ַ
#define LCD_Width 800                       //	LCD�����س���
#define LCD_Height 480                      //	LCD�����ؿ��
#define Color_Mode LTDC_PIXEL_FORMAT_RGB565 //	��ɫ��ʽ

#define LCD_WHITE 0xffFFFFFF // ����ɫ
#define LCD_BLACK 0xff000000 // ����ɫ

#define LCD_BLUE 0xff0000FF    //	����ɫ
#define LCD_GREEN 0xff00FF00   //	����ɫ
#define LCD_RED 0xffFF0000     //	����ɫ
#define LCD_CYAN 0xff00FFFF    //	����ɫ
#define LCD_MAGENTA 0xffFF00FF //	�Ϻ�ɫ
#define LCD_YELLOW 0xffFFFF00  //	��ɫ
#define LCD_GREY 0xff2C2C2C    //	��ɫ

#define LIGHT_BLUE 0xff8080FF    //	����ɫ
#define LIGHT_GREEN 0xff80FF80   //	����ɫ
#define LIGHT_RED 0xffFF8080     //	����ɫ
#define LIGHT_CYAN 0xff80FFFF    //	������ɫ
#define LIGHT_MAGENTA 0xffFF80FF //	���Ϻ�ɫ
#define LIGHT_YELLOW 0xffFFFF80  //	����ɫ
#define LIGHT_GREY 0xffA3A3A3    //	����ɫ

#define DARK_BLUE 0xff000080    //	����ɫ
#define DARK_GREEN 0xff008000   //	����ɫ
#define DARK_RED 0xff800000     //	����ɫ
#define DARK_CYAN 0xff008080    //	������ɫ
#define DARK_MAGENTA 0xff800080 //	���Ϻ�ɫ
#define DARK_YELLOW 0xff808000  //	����ɫ
#define DARK_GREY 0xff404040    //	����ɫ

#define pink  0XFFC0CB       //�ۺ�ɫ
#define lightcoral   0XFF7F50       //ɺ��ɫ
#define fleshcolor  0XFF7D40       //��ɫ
#define dodgerblue  0X1E90FF       //��ʯ��ɫ
#define tinzenite  0X03A89E       //����ɫ
#define Tomato_red  0XFF6347       //���Ѻ�
#define nacarat  0XFF4500      //�ۺ�
#define peacock_blue  0X33A1C9      //��ȸ��
#define turquoise_blue  0X00C78C      //��������ɫ




void LCD_CopyBuffer(uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint32_t *color);         

void color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color);
void lcd_clear(uint16_t color);
uint16_t color_change(uint32_t Color);

/*�������ܺ���*/
void LCD_DrawPoint(uint16_t x, uint16_t y, uint32_t color);
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color);
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color_biu);


#endif
/**************************
ǳ���� 176	224	230	0XB0E0E6
Ʒ��	65	105	225	0X4169E1
ʯ����	106	90	205	0X6A5ACD
����	135	206	235	0X87CEEB
				
��ɫ	0	255	255	0X00FFFF
����	56	94	15	0X385E0F
����	8	46	84	0X082E54
����ɫ	127	255	212	0X7FFFD4
����ɫ	64	224	208	0X40E0D0
��ɫ	0	255	0	0X00FF00
����ɫ	127	255	0	0X7FFF00
����ɫ	61	145	64	0X3D9140
����ɫ	0	201	87	0X00C957
ɭ����	34	139	34	0X228B22
�ݵ���	124	252	0	0X7CFC00
�����	50	205	50	0X32CD32
����ɫ	189	252	201	0XBDFCC9
����ɫ	107	142	35	0X6B8E23
����ɫ	48	128	20	0X308014
����ɫ	46	139	87	0X2E8B57
����ɫ	0	255	127	0X00FF7F
				
��ɫ	160	32	240	0XA020F0
������ 138	43	226	0X8A2BE2
jasoa	160	102	211	0XA066D3
����ɫ	153	51	250	0X9933FA
����ɫ	218	112	214	0XDA70D6
÷��ɫ	221	160	221	0XDDA0DD
**************************/
