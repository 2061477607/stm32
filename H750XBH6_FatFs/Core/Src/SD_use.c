#include "SD_use.h"
#include "fatfs.h"
#include <stdio.h>
#include "ffconf.h"	

int32_t SD_Status ; 		 //SD������־λ
FATFS 	SD_FatFs; 		// �ļ�ϵͳ����
FRESULT File_Res;    // ������� 

uint32_t SD_ReadBuffer[512*64/4];	//	����������
BYTE 	MyFile_ReadBuffer[1024];	//Ҫ����������
extern UART_HandleTypeDef huart4;

char FR_Table[20][30]=
{
    "FR_OK", 				    /* (0) Succeeded */
	"FR_DISK_ERR",			/* (1) A hard error occurred in the low level disk I/O layer */
	"FR_INT_ERR",				/* (2) Assertion failed */
	"FR_NOT_READY",			/* (3) The physical drive cannot work */
	"FR_NO_FILE",				/* (4) Could not find the file */
	"FR_NO_PATH",				/* (5) Could not find the path */
	"FR_INVALID_NAME",		/* (6) The path name format is invalid */
	"FR_DENIED",				/* (7) Access denied due to prohibited access or directory full */
	"FR_EXIST",				/* (8) Access denied due to prohibited access */
	"FR_INVALID_OBJECT",		/* (9) The file/directory object is invalid */
	"FR_WRITE_PROTECTED",		/* (10) The physical drive is write protected */
	"FR_INVALID_DRIVE",		/* (11) The logical drive number is invalid */
	"FR_NOT_ENABLED",			/* (12) The volume has no work area */
	"FR_NO_FILESYSTEM",		/* (13) There is no valid FAT volume */
	"FR_MKFS_ABORTED",		/* (14) The f_mkfs() aborted due to any problem */
	"FR_TIMEOUT",				/* (15) Could not get a grant to access the volume within defined period */
	"FR_LOCKED",				/* (16) The operation is rejected according to the file sharing policy */
	"FR_NOT_ENOUGH_CORE",		/* (17) LFN working buffer could not be allocated */
	"FR_TOO_MANY_OPEN_FILES",	/* (18) Number of open files > _FS_LOCK */
	"FR_INVALID_PARAMETER"	/* (19) Given parameter is invalid */
};
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

void FatFs_GetVolume(void)	// �����豸����
{
	FATFS *fs;		//����ṹ��ָ��
	uint32_t SD_CardCapacity = 0;		//SD����������
	uint32_t SD_FreeCapacity = 0;		//SD����������
	DWORD fre_clust, fre_sect, tot_sect; 	//���дأ���������������������

	f_getfree("0:",&fre_clust,&fs);			//��ȡSD��ʣ��Ĵ�

	tot_sect = (fs->n_fatent-2) * fs->csize;	//���������� = �ܵĴ� * ÿ���ذ�����������
	fre_sect = fre_clust * fs->csize;			//����ʣ��Ŀ���������	   

	SD_CardCapacity = tot_sect / 2048 ;	// SD�������� = �������� * 512( ÿ�������ֽ��� ) / 1048576(�����MB)
	SD_FreeCapacity = fre_sect / 2048 ;	//����ʣ�����������λΪM
	printf("-------------------��ȡ�豸������Ϣ-----------------\r\n");		
	printf("SD������%dMB\r\n",SD_CardCapacity);	
	printf("SDʣ�ࣺ%dMB\r\n",SD_FreeCapacity);
}
uint8_t  FatFs_FileTest(void)	//�ļ�������д�����
{
	uint8_t i = 0;
	uint16_t BufferSize = 0;	
	FIL	MyFile;			// �ļ�����
	UINT 	MyFile_Num;		//	���ݳ���
	BYTE 	MyFile_WriteBuffer[] = "STM32H750 SD�� �ļ�ϵͳ����\n";	//Ҫд�������
	
	
	printf("-------------FatFs �ļ�������д�����---------------\r\n");
	
	File_Res = f_open(&MyFile,"0:FatFs Test.txt",FA_CREATE_ALWAYS | FA_WRITE);	//���ļ������������򴴽����ļ�
	if(File_Res == FR_OK)
	{
		printf("�ļ���/�����ɹ���׼��д������...\r\n");
		
		File_Res = f_write(&MyFile,MyFile_WriteBuffer,sizeof(MyFile_WriteBuffer),&MyFile_Num);	//���ļ�д������
		if (File_Res == FR_OK)	
		{
            
			printf("д��ɹ���д������Ϊ��\r\n");
            HAL_Delay(100);
            HAL_UART_Transmit(&huart4, (uint8_t *)&MyFile_WriteBuffer, sizeof(MyFile_WriteBuffer), 100);
		}
		else
		{
			printf("�ļ�д��ʧ�ܣ�����SD�������¸�ʽ��!\r\n");
			f_close(&MyFile);	  //�ر��ļ�	
			return ERROR;			
		}
		f_close(&MyFile);	  //�ر��ļ�			
	}
	else
	{
		printf("�޷���/�����ļ�������SD�������¸�ʽ��!\r\n");
		f_close(&MyFile);	  //�ر��ļ�	
		return ERROR;		
	}
	
	printf("-------------FatFs �ļ���ȡ����---------------\r\n");	
	
	BufferSize = sizeof(MyFile_WriteBuffer)/sizeof(BYTE);									// ����д������ݳ���
	File_Res = f_open(&MyFile,"0:FatFs Test.txt",FA_OPEN_EXISTING | FA_READ);	//���ļ������������򴴽����ļ�
	File_Res = f_read(&MyFile,MyFile_ReadBuffer,BufferSize,&MyFile_Num);			// ��ȡ�ļ�
	if(File_Res == FR_OK)
	{
		printf("�ļ���ȡ�ɹ�������У������...\r\n");
		
		for(i=0;i<BufferSize;i++)
		{
			if(MyFile_WriteBuffer[i] != MyFile_ReadBuffer[i])		// У������
			{
				printf("У��ʧ�ܣ�����SD�������¸�ʽ��!\r\n");
				f_close(&MyFile);	  //�ر��ļ�	
				return ERROR;
			}
		}
        HAL_Delay(100);
		printf("У��ɹ�������������Ϊ��\r\n");
		printf("%s\n",MyFile_ReadBuffer);
	}	
	else
	{
		printf("�޷���ȡ�ļ�������SD�������¸�ʽ��!\r\n");
		f_close(&MyFile);	  //�ر��ļ�	
		return ERROR;		
	}	
	
	f_close(&MyFile);	  //�ر��ļ�	
	return SUCCESS;
}
void FatFs_Check(void)	//�ж�FatFs�Ƿ���سɹ�����û�д���FatFs���ʽ��SD��
{
	BYTE work[_MAX_SS]; 
	
	FATFS_LinkDriver(&SD_Driver, SDPath);		// ��ʼ������
	File_Res = f_mount(&SD_FatFs,"0:",1);	//	����SD��
	
	if (File_Res == FR_OK)	//�ж��Ƿ���سɹ�
	{
		printf("\r\nSD�ļ�ϵͳ���سɹ�\r\n");
	}
	else		
	{
		printf("SD����δ�����ļ�ϵͳ��������ʽ��\r\n");
		
		File_Res = f_mkfs("0:",FM_FAT32,0,work,sizeof work);		//��ʽ��SD����FAT32����Ĭ�ϴ�С16K
		
		if (File_Res == FR_OK)		//�ж��Ƿ��ʽ���ɹ�
			printf("SD����ʽ���ɹ���\r\n");
		else
			printf("��ʽ��ʧ�ܣ���������SD����\r\n");
	}
}
/*------------------------------------------���ܺ���-------------------------------------------------------------*/

/*
*********************************************************************************************************
* �� �� ��: ViewRootDir
* ����˵��: ��ʾ SD ����Ŀ¼�µ��ļ���
* �� �Σ���
* �� �� ֵ: ��
*********************************************************************************************************
*/
extern SD_HandleTypeDef hsd1;
void ViewRootDir(void)
{
    FRESULT result;
    uint32_t cnt = 0;
    FILINFO fno,FileInf;
    char DiskPath[]="0:";
    DIR DirInf;
    /* �����ļ�ϵͳ */
    result = f_mount(&SD_FatFs, DiskPath, 0); /* Mount a logical drive */
    if (result != FR_OK)
    {
        printf("�����ļ�ϵͳʧ�� (%s)\r\n", FR_Table[result]);
    }
    /* �򿪸��ļ��� */
    result = f_opendir(&DirInf, DiskPath); /* ���������������ӵ�ǰĿ¼��ʼ */
    if (result != FR_OK)
    {
        printf("�򿪸�Ŀ¼ʧ�� (%s)\r\n", FR_Table[result]);
        return;
    }
        printf("���� | �ļ���С | ���ļ��� | ���ļ���\r\n");
    for (cnt = 0; ;cnt++)
    {
        result = f_readdir(&DirInf, &FileInf); /* ��ȡĿ¼��������Զ����� */
    if (result != FR_OK || FileInf.fname[0] == 0)
    {
        break;
    }
    if (FileInf.fname[0] == '.')
    {
    continue;
    }
    /* �ж����ļ�������Ŀ¼ */
    if (FileInf.fattrib & AM_DIR)
    {
        printf("(0x%02d)Ŀ¼ ", FileInf.fattrib);
    }
    else
    {
        printf("(0x%02d)�ļ� ", FileInf.fattrib);
    }
    f_stat(FileInf.fname, &fno);
    /* ��ӡ�ļ���С, ��� 4G */
    printf(" %10d", (int)fno.fsize);
    printf(" %s\r\n", (char *)FileInf.fname); /* ���ļ��� */
    }
    /* ��ӡ���ٶ���Ϣ */
    if(hsd1.SdCard.CardSpeed == CARD_NORMAL_SPEED)
    {
        printf("Normal Speed Card <12.5MB/S, MAX Clock < 25MHz, Spec Version 1.01\r\n");
    }
    else if (hsd1.SdCard.CardSpeed == CARD_HIGH_SPEED)
    {
        printf("High Speed Card <25MB/s, MAX Clock < 50MHz, Spec Version 2.00\r\n");
    }
    else if (hsd1.SdCard.CardSpeed == CARD_ULTRA_HIGH_SPEED)
    {
        printf("UHS-I SD Card <50MB/S for SDR50, DDR50 Cards, MAX Clock < 50MHz OR 100MHz\r\n");
        printf("UHS-I SD Card <104MB/S for SDR104, MAX Clock < 108MHz, Spec version 3.01\r\n");
    }
    /* ж���ļ�ϵͳ */
    f_mount(NULL, DiskPath, 0);
}


