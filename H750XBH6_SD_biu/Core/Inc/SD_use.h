#ifndef __SD_USE_H_
#define __SD_USE_H_

#include "main.h"
#include "fatfs.h"


void show_sdcard_info(SD_HandleTypeDef hsd);
void FatFs_Check(void);				// �ж�FatFs�Ƿ���سɹ�����û�д���FatFs���ʽ��SD��
void FatFs_GetVolume(void);		// �����豸����
uint8_t  FatFs_FileTest(void);	// �ļ�������д�����
void ViewRootDir(void);//��ʾ SD ����Ŀ¼�µ��ļ���
uint8_t Find_bin_file(char* binPath);
uint8_t bin_load(char* bin_PATH);
#endif

