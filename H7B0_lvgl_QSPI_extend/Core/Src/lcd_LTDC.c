#include "lcd_LTDC.h"

static pFONT *LCD_Fonts; // Ӣ������
extern DMA2D_HandleTypeDef hdma2d;	// DMA2D���
void color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color)
{
     uint16_t x, y;
     if (sx <= ex)
     {
          for (x = sx; x <= ex; x++)
          {
               if (sy < ey)
               {
                    for (y = sy; y <= ey; y++)
                         lcd_draw_point(x, y, color);
               }
               else
               {
                    for (y = ey; y <= sy; y++)
                         lcd_draw_point(x, y, color);
               }
          }
     }
     else
     {
          for (x = ex; x <= sx; x++)
          {
               if (sy < ey)
               {
                    for (y = sy; y <= ey; y++)
                         lcd_draw_point(x, y, color);
               }
               else
               {
                    for (y = ey; y <= sy; y++)
                         lcd_draw_point(x, y, color);
               }
          }
     }
}

void draw_circle(int16_t sx, int16_t sy, uint16_t radius, uint32_t color)
{
     int16_t x = 0, y = 0;
     if (sx - radius > 0)
          x = sx - radius;
     if (sy - radius > 0)
          y = sy - radius;
     else
          y = 0;
     for (; x < sx + radius; x++)
     {
          if (sy - radius > 0)
               y = sy - radius;
          else
               y = 0;
          for (; y < sy + radius; y++)
          {
               if (((x - sx) * (x - sx) + (y - sy) * (y - sy)) <= radius * radius)
               {

                    lcd_fill(x, y, 1, 1, color);
               }
          }
     }
}
void lcd_clear(uint16_t color)
{

     uint16_t *ptr = (uint16_t *)(0x24000000);

     uint32_t i = 0;

     while (i < 800 * 480)
     {

          *(ptr + i++) = color;
     }
}
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
     uint16_t *ptr = (uint16_t *)(0x24000000);
    if(x<=LCD_Width&&y<=LCD_Height)
        *(ptr + y * LCD_Width + x) = color;
    else
        return;
}
void LCD_DrawPoint(uint16_t x, uint16_t y, uint32_t color)
{
     uint16_t *ptr = (uint16_t *)(0x24000000);
     if (Color_Mode == LTDC_PIXEL_FORMAT_RGB565)
     {
          color = color_change(color);
     }
     *(ptr + y * 800 + x) = color;
}
static void _DMA2D_Fill(void *pDst,
                        uint32_t xSize,
                        uint32_t ySize,
                        uint32_t OffLine,
                        uint32_t ColorIndex,
                        uint32_t PixelFormat)
{

     /* DMA2D ���üĴ������洢��ģʽ, ����ģʽ�ò���ǰ����ͱ����� */
     DMA2D->CR &= ~(DMA2D_CR_START); //	ֹͣDMA2D
     DMA2D->CR = DMA2D_R2M;
     DMA2D->OCOLR = ColorIndex;
     DMA2D->OMAR = (uint32_t)pDst;
     DMA2D->OOR = OffLine;
     DMA2D->OPFCCR = PixelFormat;
     DMA2D->NLR = (uint32_t)(xSize << 16) | (uint16_t)ySize;

     /* �������� */
     DMA2D->CR |= DMA2D_CR_START;

     /* �ȴ� DMA2D ������� */
     while (DMA2D->CR & DMA2D_CR_START)
     {
     }
}
uint16_t color_change(uint32_t Color)
{
     uint16_t Red_Value = 0, Green_Value = 0, Blue_Value = 0;
     Red_Value = (uint16_t)((Color & 0x00F80000) >> 8);
     Green_Value = (uint16_t)((Color & 0x0000FC00) >> 5);
     Blue_Value = (uint16_t)((Color & 0x000000F8) >> 3);
     return (uint16_t)(Red_Value | Green_Value | Blue_Value);
}

void lcd_fill0(uint16_t sx, uint16_t sy, uint16_t x, uint16_t y, uint32_t color_biu)
{
     uint32_t date_address;
     uint16_t color;
     if (Color_Mode == LTDC_PIXEL_FORMAT_RGB565)
     {
          color = color_change(color_biu);
     }
     date_address = LCD_MemoryAdd + sy * LCD_Width * 2 + sx * 2;

     y++;
     _DMA2D_Fill((void *)(date_address), x, y, LCD_Width - x, color, Color_Mode);
}
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t x, uint16_t y, uint16_t color_biu)
{
     uint32_t date_address;
     
     date_address = LCD_MemoryAdd + sy * LCD_Width * 2 + sx * 2;
    
     
    
     _DMA2D_Fill((void *)(date_address), x, y, LCD_Width - x, color_biu, Color_Mode);
}
/***************************************************************************************************************
 *	�� �� ��:	LCD_DisplayChar
 *
 *	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~799
 *					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~479
 *					c  - ASCII�ַ�
 *
 *	��������:	��ָ��������ʾָ�����ַ�
 *
 *	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetFont(&Font24) ����Ϊ 2412��ASCII����
 *					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0xff0000FF) ����Ϊ��ɫ
 *					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0xff000000) ����Ϊ��ɫ�ı���ɫ
 *					4. ʹ��ʾ�� LCD_DisplayChar( 10, 10, 'a') ��������(10,10)��ʾ�ַ� 'a'
 *
 ***************************************************************************************************************/

void LCD_DisplayChar(uint16_t x, uint16_t y, uint8_t c, uint32_t color)
{
     uint16_t index = 0, counter = 0; // ��������
     uint8_t disChar;                 // �洢�ַ��ĵ�ַ
     uint16_t Xaddress = x;           // ˮƽ����

     c = c - 32; // ����ASCII�ַ���ƫ��
     if (Color_Mode == LTDC_PIXEL_FORMAT_RGB565)
     {
          color = color_change(color);
     }
     for (index = 0; index < LCD_Fonts->Sizes; index++)
     {
          disChar = LCD_Fonts->pTable[c * LCD_Fonts->Sizes + index]; // ��ȡ�ַ���ģֵ
          for (counter = 0; counter < 8; counter++)
          {
               if (disChar & 0x01)
               {
                    lcd_draw_point(Xaddress, y, color); // ��ǰģֵ��Ϊ0ʱ��ʹ�û���ɫ���
               }

               disChar >>= 1;
               Xaddress++; // ˮƽ�����Լ�

               if ((Xaddress - x) == LCD_Fonts->Width) // ���ˮƽ����ﵽ���ַ���ȣ����˳���ǰѭ��
               {                                       // ������һ�еĻ���
                    Xaddress = x;
                    y++;
                    break;
               }
          }
     }
}
void LCD_DisplayString(uint16_t x, uint16_t y, char *p, uint32_t color)
{
     while ((x < LCD_Width) && (*p != 0)) // �ж���ʾ�����Ƿ񳬳���ʾ�������ַ��Ƿ�Ϊ���ַ�
     {
          LCD_DisplayChar(x, y, *p, color);
          x += LCD_Fonts->Width; // ��ʾ��һ���ַ�
          p++;                   // ȡ��һ���ַ���ַ
     }
}
/***************************************************************************************************************
 *	�� �� ��:	LCD_SetTextFont
 *
 *	��ڲ���:	*fonts - Ҫ���õ��ı�����
 *
 *	��������:	�����ı����壬�������ĺ�ASCII�ַ���
 *
 *	˵    ��:	1. ��ѡ��ʹ�� 3232/2424/2020/1616/1212 ���ִ�С���������壬
 *						���Ҷ�Ӧ������ASCII����Ϊ 3216/2412/2010/1608/1206
 *					2. �����ģ����� lcd_fonts.c
 *					3. �����ֿ�ʹ�õ���С�ֿ⣬���õ��˶�Ӧ�ĺ�����ȥȡģ
 *					4. ʹ��ʾ�� LCD_SetTextFont(&CH_Font24) �������� 2424�����������Լ�2412��ASCII�ַ�����
 *
 ***************************************************************************************************************/

void LCD_SetTextFont(pFONT *fonts)
{
     LCD_Fonts = fonts; // ������������
     switch (fonts->Width)
     {
     case 12:
          LCD_Fonts = &Font12;
          break; // ����ASCII�ַ�������Ϊ 1206
     case 16:
          LCD_Fonts = &Font16;
          break; // ����ASCII�ַ�������Ϊ 1608
     case 20:
          LCD_Fonts = &Font20;
          break; // ����ASCII�ַ�������Ϊ 2010
     case 24:
          LCD_Fonts = &Font24;
          break; // ����ASCII�ַ�������Ϊ 2412
     case 32:
          LCD_Fonts = &Font32;
          break; // ����ASCII�ַ�������Ϊ 3216
     default:
          break;
     }
}
/***************************************************************************************************************************************
 *	�� �� ��: LCD_DrawLine
 *
 *	��ڲ���: x1 - ��� ˮƽ���꣬ȡֵ��Χ 0~799
 *			 	 y1 - ��� ��ֱ���꣬ȡֵ��Χ 0~479
 *
 *				 x2 - �յ� ˮƽ���꣬ȡֵ��Χ 0~799
 *            y2 - �յ� ��ֱ���꣬ȡֵ��Χ 0~479
 *
 *	��������: ������֮�仭��
 *
 *	˵    ��: �ú�����ֲ��ST�ٷ������������
 *
 *****************************************************************************************************************************************/

#define ABS(X) ((X) > 0 ? (X) : -(X))

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color)
{
     int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
             yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
             curpixel = 0;

     deltax = ABS(x2 - x1); /* The difference between the x's */
     deltay = ABS(y2 - y1); /* The difference between the y's */
     x = x1;                /* Start x off at the first pixel */
     y = y1;                /* Start y off at the first pixel */

     if (x2 >= x1) /* The x-values are increasing */
     {
          xinc1 = 1;
          xinc2 = 1;
     }
     else /* The x-values are decreasing */
     {
          xinc1 = -1;
          xinc2 = -1;
     }

     if (y2 >= y1) /* The y-values are increasing */
     {
          yinc1 = 1;
          yinc2 = 1;
     }
     else /* The y-values are decreasing */
     {
          yinc1 = -1;
          yinc2 = -1;
     }

     if (deltax >= deltay) /* There is at least one x-value for every y-value */
     {
          xinc1 = 0; /* Don't change the x when numerator >= denominator */
          yinc2 = 0; /* Don't change the y for every iteration */
          den = deltax;
          num = deltax / 2;
          numadd = deltay;
          numpixels = deltax; /* There are more x-values than y-values */
     }
     else /* There is at least one y-value for every x-value */
     {
          xinc2 = 0; /* Don't change the x for every iteration */
          yinc1 = 0; /* Don't change the y when numerator >= denominator */
          den = deltay;
          num = deltay / 2;
          numadd = deltax;
          numpixels = deltay; /* There are more y-values than x-values */
     }
     for (curpixel = 0; curpixel <= numpixels; curpixel++)
     {
          LCD_DrawPoint(x, y, color); /* Draw the current pixel */
          num += numadd;              /* Increase the numerator by the top of the fraction */
          if (num >= den)             /* Check if numerator >= denominator */
          {
               num -= den; /* Calculate the new numerator value */
               x += xinc1; /* Change the x as appropriate */
               y += yinc1; /* Change the y as appropriate */
          }
          x += xinc2; /* Change the x as appropriate */
          y += yinc2; /* Change the y as appropriate */
     }
}
/***************************************************************************************************************************************
 *	�� �� ��: LCD_DrawRect
 *
 *	��ڲ���: x - ��ʼˮƽ���꣬ȡֵ��Χ0~799
 *				 y - ��ʼ��ֱ���꣬ȡֵ��Χ0~479
 *			 	 width  - ���ε�ˮƽ��ȣ����ȡֵLCD_Width
 *				 height - ���εĴ�ֱ��ȣ����ȡֵLCD_height
 *
 *	��������: ��ָ��λ�û���ָ������ľ�������
 *
 *	˵    ��: �ú�����ֲ��ST�ٷ������������
 *
 *****************************************************************************************************************************************/

void LCD_DrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color)
{
     /* draw horizontal lines */
     LCD_DrawLine(x, y, x + width, y, color);
     LCD_DrawLine(x, y + height, x + width, y + height, color);

     /* draw vertical lines */
     LCD_DrawLine(x, y, x, y + height, color);
     LCD_DrawLine(x + width, y, x + width, y + height, color);
}
/***************************************************************************************************************************************
 *	�� �� ��: LCD_DrawCircle
 *
 *	��ڲ���: x - Բ�� ˮƽ���꣬ȡֵ��Χ 0~799
 *			 	 y - Բ�� ��ֱ���꣬ȡֵ��Χ 0~479
 *			 	 r  - �뾶
 *
 *	��������: ������ (x,y) ���ư뾶Ϊ r ��Բ������
 *
 *	˵    ��: 1. �ú�����ֲ��ST�ٷ������������
 *				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
 *
 *****************************************************************************************************************************************/

void LCD_DrawCircle(uint16_t x, uint16_t y, uint16_t r, uint32_t color)
{
     int Xadd = -r, Yadd = 0, err = 2 - 2 * r, e2;
     do
     {

          LCD_DrawPoint(x - Xadd, y + Yadd, color);
          LCD_DrawPoint(x + Xadd, y + Yadd, color);
          LCD_DrawPoint(x + Xadd, y - Yadd, color);
          LCD_DrawPoint(x - Xadd, y - Yadd, color);

          e2 = err;
          if (e2 <= Yadd)
          {
               err += ++Yadd * 2 + 1;
               if (-Xadd == Yadd && e2 <= Xadd)
                    e2 = 0;
          }
          if (e2 > Xadd)
               err += ++Xadd * 2 + 1;
     } while (Xadd <= 0);
}
/***************************************************************************************************************************************
 *	�� �� ��: LCD_FillCircle
 *
 *	��ڲ���: x - Բ�� ˮƽ���꣬ȡֵ��Χ 0~799
 *			 	 y - Բ�� ��ֱ���꣬ȡֵ��Χ 0~479
 *			 	 r  - �뾶
 *
 *	��������: ������ (x,y) ���뾶Ϊ r ��Բ������
 *
 *	˵    ��: 1. �ú�����ֲ��ST�ٷ������������
 *				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
 *
 *****************************************************************************************************************************************/

void LCD_FillCircle(uint16_t x, uint16_t y, uint16_t r, uint32_t color)
{
     int32_t D;     /* Decision Variable */
     uint32_t CurX; /* Current X Value */
     uint32_t CurY; /* Current Y Value */

     D = 3 - (r << 1);

     CurX = 0;
     CurY = r;

     while (CurX <= CurY)
     {
          if (CurY > 0)
          {
               LCD_DrawLine(x - CurX, y - CurY, x - CurX, y - CurY + 2 * CurY, color);
               LCD_DrawLine(x + CurX, y - CurY, x + CurX, y - CurY + 2 * CurY, color);
          }

          if (CurX > 0)
          {
               LCD_DrawLine(x - CurY, y - CurX, x - CurY, y - CurX + 2 * CurX, color);
               LCD_DrawLine(x + CurY, y - CurX, x + CurY, y - CurX + 2 * CurX, color);
          }
          if (D < 0)
          {
               D += (CurX << 2) + 6;
          }
          else
          {
               D += ((CurX - CurY) << 2) + 10;
               CurY--;
          }
          CurX++;
     }

     LCD_DrawCircle(x, y, r, color);
}
void lcd_draw_image(uint16_t sx,uint16_t sy,uint16_t w,uint16_t h,uint8_t* image)
{
    uint16_t x,y,color;
    uint32_t i=0;
    
    
    for(y=0;y<h;y++)
    {
        for(x=0;x<w;x++)
        {
            color=((uint16_t)image[i]<<8)+image[++i];
            lcd_draw_point(x+sx, y+sy, color);
            i++;
        }
        
    }
    
}
void LCD_CopyBuffer(uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint32_t *color)
{

	DMA2D->CR	  &=	~(DMA2D_CR_START);				//	ֹͣDMA2D
	DMA2D->CR		=	DMA2D_M2M;							//	�洢�����洢��
	DMA2D->FGPFCCR	=	LTDC_PIXEL_FORMAT_RGB565;		//	������ɫ��ʽ
   DMA2D->FGOR    =  0;										// 
	DMA2D->OOR		=	LCD_Width - width;				//	������ƫ�� 	
	DMA2D->FGMAR   =  (uint32_t)color;		
	DMA2D->OMAR		=	LCD_MemoryAdd + 2*(LCD_Width * y + x);	// ��ַ;
	DMA2D->NLR		=	(width<<16)|(height);			//	�趨���ȺͿ��		
	DMA2D->CR	  |=	DMA2D_CR_START;					//	����DMA2D
		
	while (DMA2D->CR & DMA2D_CR_START) ;			//	�ȴ��������

}



