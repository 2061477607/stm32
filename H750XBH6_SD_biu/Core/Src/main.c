/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "sdmmc.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "SD_use.h"
#include "qspi_w25q64.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/********************************************** �������� *******************************************/

typedef  void (*pFunction)(void);

pFunction JumpToApplication;
extern uint8_t SD_use;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    char bin_PATH[20];
    uint8_t key_status=0;
    uint16_t time_num=0;
    
  /* USER CODE END 1 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SDMMC1_SD_Init();
  MX_UART4_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */
  
    LED_R_GPIO_Port->ODR|=LED_R_Pin;
    LED_B_GPIO_Port->ODR|=LED_B_Pin;
    QSPI_W25Qxx_Init();	  				 // ��ʼ��W25Q64
    
    if(SD_use==0)
    {   
        FatFs_Check();			//�ж�FatFs�Ƿ���سɹ�����û�д���FatFs���ʽ��SD��

        ViewRootDir();          //�����Ŀ¼�ļ���Ϣ
        printf("-----------------------------------------------------------------\n");
        if(Find_bin_file(bin_PATH)==1)//SD������bin�ļ���ִ�й���ѡ��
        {
            printf("���ҵ�bin�ļ�:%s\n",bin_PATH);
            printf("-------------------------------------------------------------------\n");
            printf("���������ڰ��°���������bin�ļ���������ģʽ\n");
            time_num=0;
            while(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin)==1)
            {
                time_num++;
                HAL_Delay(10);
                if(time_num>300){
                    key_status=0;
                    break;
                }
            }
            if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin)==0)
                key_status=1;
            else
                key_status=0;
            if(key_status)
            {
                printf("-------------------------------------------------------------------\n");
                printf("��⵽�������룬��������bin�ļ���������ģʽ\n");       
                printf("ģʽ SD:bin�ļ�-->QSPI flash \n");
                bin_load(bin_PATH);//����bin�ļ�
                printf("������flash��������ִ��");
            }
            else
            {
                printf("-------------------------------------------------------------------\n");
                printf("������ʱ\n");       
                printf("������flash��������ִ��");
            }
    /*-----------------------��flash��������-----------------------------------------------------------*/        
            QSPI_W25Qxx_MemoryMappedMode(); 	 // ����QSPIΪ�ڴ�ӳ��ģʽ
            SCB_DisableICache();		// �ر�ICache
            SCB_DisableDCache();		// �ر�Dcache

            
            SysTick->CTRL = 0;		// �ر�SysTick
            SysTick->LOAD = 0;		// ��������ֵ
            SysTick->VAL = 0;			// �������ֵ

            JumpToApplication = (pFunction) (*(__IO uint32_t*) (W25Qxx_Mem_Addr + 4));	// ������ʼ��ַ
            __set_MSP(*(__IO uint32_t*) W25Qxx_Mem_Addr);	// ��������ջָ��
            printf("��ת��W25Q64�����û�����>>>\r\n\r\n");

            JumpToApplication();			// ִ����ת
        }
        else//SD����û��bin�ļ���ִ������
            printf("δ��SD����Ŀ¼�﷢��bin�ļ�\n");
    }
    else
    {
            QSPI_W25Qxx_MemoryMappedMode(); 	 // ����QSPIΪ�ڴ�ӳ��ģʽ
            SCB_DisableICache();		// �ر�ICache
            SCB_DisableDCache();		// �ر�Dcache

            
            SysTick->CTRL = 0;		// �ر�SysTick
            SysTick->LOAD = 0;		// ��������ֵ
            SysTick->VAL = 0;			// �������ֵ

            JumpToApplication = (pFunction) (*(__IO uint32_t*) (W25Qxx_Mem_Addr + 4));	// ������ʼ��ַ
            __set_MSP(*(__IO uint32_t*) W25Qxx_Mem_Addr);	// ��������ջָ��
            printf("��ת��W25Q64�����û�����>>>\r\n\r\n");

            JumpToApplication();			// ִ����ת
    }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
      HAL_Delay(100);
      LED_R_GPIO_Port->ODR^=LED_R_Pin;
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_UART4|RCC_PERIPHCLK_SDMMC;
  PeriphClkInitStruct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL;
  PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
//  __disable_irq();
    LED_R_GPIO_Port->ODR|=LED_R_Pin;
    LED_B_GPIO_Port->ODR|=LED_B_Pin;
  while (1)
  {
    HAL_GPIO_TogglePin(LED_R_GPIO_Port,LED_R_Pin);
    HAL_Delay(100);
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
