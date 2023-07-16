#ifndef __SDBSP_H_
#define __SDBSP_H_
#include "main.h"

#define SD_TIMEOUT             ((uint32_t)0x00100000U) //�ȴ�ʱ��
#define BLOCK_SIZE            512  //�����Ŀ
#define NUMBER_OF_BLOCKS      400 //������ݴ�С

#define SD_TRANSFER_OK      ((uint8_t)0x00)             /* ������� */
#define SD_TRANSFER_BUSY    ((uint8_t)0x01)             /* ����æ */

#define MULTI_BUFFER_SIZE    (BLOCK_SIZE * NUMBER_OF_BLOCKS)
#define speed_test_size  5120
void show_sdcard_info(SD_HandleTypeDef hsd);
uint8_t sd_read_disk(uint8_t* buf, uint32_t sector, uint32_t cnt);
uint8_t sd_write_disk(uint8_t *buf, uint32_t sector, uint32_t cnt);

#endif

