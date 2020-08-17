/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint8_t addr=0xEE;
uint8_t Data=0xF6;
uint8_t test=0xD0;
uint8_t TempCode=0x2E;
uint8_t PressCode=0x34;
uint8_t CommReg=0xF4;
uint8_t AddrCalib=0xAA;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c2;

/* USER CODE BEGIN PV */
uint8_t tRXBuff[3];
uint8_t CalibData[22];
uint8_t pRXbuff[3];
uint8_t TXBuff[2];
uint16_t  AC4,AC5,AC6;
int16_t MC,MD,X1,X2,AC1,AC2,AC3,B1,B2,MB;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C2_Init(void);
/* USER CODE BEGIN PFP */
void BMP160_init(void);
uint16_t BMP180_get_UP(void);
uint16_t BMP180_get_UT (void);
uint16_t BMP180_get_Temperature(void);
uint16_t BMP180_get_Press(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

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
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
	
	TXBuff[0]=CommReg;
	TXBuff[1]=TempCode;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)addr, TXBuff, 2, (uint32_t)1000);
	TXBuff[0]=Data;
	HAL_Delay(5);
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)addr, TXBuff, 1, (uint32_t)1000);
	HAL_I2C_Master_Receive(&hi2c2, (uint16_t)addr, tRXBuff, 3, (uint32_t)1000);
	UT=(tRXBuff[0]<<8)+tRXBuff[1];
	AC5=((CalibData[8])<<8) + CalibData[9];
	AC6=((CalibData[10])<<8) + CalibData[11];;
	MC=((CalibData[18])<<8) + CalibData[19];;
	MD=((CalibData[20])<<8) + CalibData[21];;
	X1=((UT-AC6)*AC5)>>15;
	X2=(MC<<11)/(X1+MD);
  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	
    /* USER CODE BEGIN 3 */
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
void BMP180_init(void)
{	
	uint8_t Calibr[22]; 
	TXBuff[0]=AddrCalib;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)addr, TXBuff, 1, (uint32_t)1000);
	HAL_I2C_Master_Receive(&hi2c2, (uint16_t)addr, Calibr, 22, (uint32_t)1000);
	AC1=((Calibr[0])<<8)|Calibr[1];
	AC2=((Calibr[2])<<8)|Calibr[3];
	AC3=((Calibr[4])<<8)|Calibr[5];
	AC4=((Calibr[6])<<8)|Calibr[7];
	AC5=((Calibr[8])<<8)|Calibr[9];
	AC6=((Calibr[10])<<8)|Calibr[11];
	B1=((Calibr[12])<<8)|Calibr[13];
	B2=((Calibr[14])<<8)|Calibr[15];
	MB=((Calibr[16])<<8)|Calibr[17];
	MC=((Calibr[18])<<8)|Calibr[19];
	MD=((Calibr[20])<<8)|Calibr[21];
}

uint16_t BMP180_get_UT (void)
{
	uint16_t UT=0;
	TXBuff[0]=CommReg;
	TXBuff[1]=TempCode;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)addr, TXBuff, 2, (uint32_t)1000);
	TXBuff[0]=Data;
	HAL_Delay(5);
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)addr, TXBuff, 1, (uint32_t)1000);
	HAL_I2C_Master_Receive(&hi2c2, (uint16_t)addr, tRXBuff, 3, (uint32_t)1000);
	UT=(tRXBuff[0]<<8)|tRXBuff[1];
	return(UT);
}

uint16_t BMP180_get_Temperature(void)
{	
	uint16_t UT,Temperature;
	TXBuff[0]=CommReg;
	TXBuff[1]=TempCode;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)addr, TXBuff, 2, (uint32_t)1000);
	TXBuff[0]=Data;
	HAL_Delay(5);
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)addr, TXBuff, 1, (uint32_t)1000);
	HAL_I2C_Master_Receive(&hi2c2, (uint16_t)addr, tRXBuff, 3, (uint32_t)1000);
	UT=(tRXBuff[0]<<8)+tRXBuff[1];
	X1=((UT-AC6)*AC5)>>15;
	X2=(MC<<11)/(X1+MD);
	Temperature=(X1+X2+8)>>4;
	return(Temperature);
}

uint16_t BMP180_get_UP(void)
{
	uint16_t UP=0;
	TXBuff[0]=CommReg;
	TXBuff[1]=PressCode;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)addr, TXBuff, 2, (uint32_t)1000);
	TXBuff[0]=Data;
	HAL_Delay(5);
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)addr, TXBuff, 1, (uint32_t)1000);
	HAL_I2C_Master_Receive(&hi2c2, (uint16_t)addr, tRXBuff, 3, (uint32_t)1000);
	UP=(tRXBuff[0]<<8)|tRXBuff[1];
	return(UP);
}

uint16_t BMP180_get_Press(void)
{
	
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
