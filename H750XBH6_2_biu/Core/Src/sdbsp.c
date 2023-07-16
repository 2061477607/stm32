#include "sdbsp.h"
#include "sdmmc.h"
#include <stdio.h>

extern SD_HandleTypeDef hsd1;


/**
  * @brief  SD����Ϣ�������
  * @param  ��
  * @retval ��
  */
void show_sdcard_info(SD_HandleTypeDef hsd)
{
    uint64_t card_capacity;       /* SD������ */
    HAL_SD_CardCIDTypeDef sd_card_cid;
    HAL_SD_CardInfoTypeDef g_sd_card_info_handle;
    HAL_SD_GetCardCID(&hsd, &sd_card_cid);      /* ��ȡCID */
    HAL_SD_GetCardInfo(&hsd,&g_sd_card_info_handle);            /* ��ȡSD����Ϣ */

    switch (g_sd_card_info_handle.CardType)
    {
        case CARD_SDSC:
        {
            if (g_sd_card_info_handle.CardVersion == CARD_V1_X)
            {
                printf("Card Type:SDSC V1\r\n");
            }
            else if (g_sd_card_info_handle.CardVersion == CARD_V2_X)
            {
                printf("Card Type:SDSC V2\r\n");
            }
        }
            break;
        
        case CARD_SDHC_SDXC:
            printf("Card Type:SDHC\r\n");
            break;
    }

    card_capacity = (uint64_t)(g_sd_card_info_handle.LogBlockNbr) * 
    (uint64_t)(g_sd_card_info_handle.LogBlockSize); /* ����SD������ */
    /* ������ID */
    printf("Card ManufacturerID:%d\r\n", sd_card_cid.ManufacturerID); 
    /* ����Ե�ַ */               
        printf("Card RCA:%d\r\n", g_sd_card_info_handle.RelCardAdd);       
    printf("LogBlockNbr:%d \r\n", 
    (uint32_t)(g_sd_card_info_handle.LogBlockNbr));   /* ��ʾ�߼������� */
    printf("LogBlockSize:%d \r\n", 
    (uint32_t)(g_sd_card_info_handle.LogBlockSize));  /* ��ʾ�߼����С */
    /* ��ʾ���� */
    printf("Card Capacity:%d GB\r\n", (uint32_t)(card_capacity >> 20)/1024);     
    /* ��ʾ���С */         
    printf("Card BlockSize:%d\r\n\r\n", g_sd_card_info_handle.BlockSize);    
}



/**
 * @brief       ��SD������
 * @param       buf:�����ݻ�����
 * @param       sector:������ַ
 * @param       cnt:��������
 * @retval      ����ֵ:0,����;����,����;
 */
uint8_t sd_read_disk(uint8_t* buf, uint32_t sector, uint32_t cnt)
{
    uint8_t sta = HAL_OK;
    uint32_t timeout = SD_TIMEOUT;
    long long lsector = sector;
//    INTX_DISABLE();  /* �ر����ж�(POLLINGģʽ,�Ͻ��жϴ��SDIO��д����!!!) */
    
    __set_PRIMASK(1);/* ��ֹȫ���ж� */
    sta = HAL_SD_ReadBlocks(&hsd1, (uint8_t*)buf,lsector, cnt, 
    SD_TIMEOUT); /* ���sector�Ķ����� */
    /* �ȴ�SD������ */
    /* �ȴ�SD��д�� */
    while (HAL_SD_GetCardState(&hsd1) != HAL_SD_CARD_TRANSFER)
    {
        if (timeout-- == 0)
        {
            sta = 1;
            break;
        }
    }
//   INTX_ENABLE();  /* �������ж� */
    __set_PRIMASK(0);/* ʹ��ȫ���ж� */
    return sta;
}
/**
 * @brief       д���ݵ�SD��
 * @param       buf:д���ݻ�����
 * @param       sector:������ַ
 * @param       cnt:��������
 * @retval      ����ֵ:0,����;����,����;
 */
uint8_t sd_write_disk(uint8_t *buf, uint32_t sector, uint32_t cnt)
{
    uint8_t sta = HAL_OK;
    uint32_t timeout = SD_TIMEOUT;
    long long lsector = sector;
    __set_PRIMASK(1);/* ��ֹȫ���ж� */
    sta = HAL_SD_WriteBlocks(&hsd1, (uint8_t*)buf, lsector, cnt, 
    SD_TIMEOUT); /* ���sector��д���� */
        
    /* �ȴ�SD��д�� */
    while (HAL_SD_GetCardState(&hsd1) != HAL_SD_CARD_TRANSFER)
    {
        if (timeout-- == 0)
        {
            sta = 1;
            break;
        }
    }
    __set_PRIMASK(0);/* ʹ��ȫ���ж� */
    return sta;
}

