/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ds18b20.h"
#include "lcd.h"
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
float temp;
float temp_set = 20.0;
float temp_set_max = 35.0;
float temp_set_min = 15.0;
char lcd_str[30];

uint8_t setting_mode = 0;
uint32_t lastDebounceTime = 0;
uint32_t debounceDelay = 50;

uint8_t fan_state = 0;
uint8_t setState = 0;
uint8_t lastsetState = 0;
uint8_t upState = 0;
uint8_t lastupState = 0;
uint8_t downState = 0;
uint8_t lastdownState = 0;


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
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

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
  /* USER CODE BEGIN 2 */
  delay_us_dwt_init();
  onewire_reset();

  LCD_Init();
  LCD_Write("     EE3031", 1);
  LCD_Write("GIA HUY  2252267", 2);
  for (uint8_t i = 0; i < 10 ; i++){
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	HAL_Delay(200);
  }

  LCD_Clear();
  LCD_Write("  CAR ATC V1.0", 1);
  LCD_Write("  Welcome User", 2);
  for (uint8_t i = 0; i < 10 ; i++){
  	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  	HAL_Delay(200);
  }

  LCD_Clear();
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
  HAL_Delay(100);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  setState = HAL_GPIO_ReadPin(SET_GPIO_Port, SET_Pin);
	  upState = HAL_GPIO_ReadPin(UP_GPIO_Port, UP_Pin);
	  downState = HAL_GPIO_ReadPin(DOWN_GPIO_Port, DOWN_Pin);

	  // Debounce for SET button
//	  if (setState == GPIO_PIN_RESET && lastsetState == GPIO_PIN_SET && (HAL_GetTick() - lastDebounceTime > debounceDelay)) {
	  if (setState == GPIO_PIN_RESET && lastsetState == GPIO_PIN_SET) {
		  lastDebounceTime = HAL_GetTick();
		  if (!setting_mode) {
			  setting_mode = 1;
			  HAL_GPIO_WritePin(FAN_GPIO_Port, FAN_Pin, 0);
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
			  LCD_Clear();
			  LCD_Write(" SET TEMP MODE", 1);
			  sprintf(lcd_str, "New set temp: %.0f", temp_set);
			  LCD_Write(lcd_str, 2);
			  HAL_Delay(50);
		  } else {
			  setting_mode = 0;
			  LCD_Clear();
			  HAL_Delay(50);
		  }
	  }
	  lastsetState = setState;

	  if (setting_mode) {
		  if (upState == GPIO_PIN_RESET && lastupState == GPIO_PIN_SET){
			  temp_set += 1;
			  if (temp_set > temp_set_max) temp_set = temp_set_max;
			  LCD_Clear();
			  LCD_Write(" SET TEMP MODE", 1);
			  sprintf(lcd_str, "New set temp: %.0f", temp_set);
			  LCD_Write(lcd_str, 2);
			  HAL_Delay(50);
		  }
		  lastupState = upState;

		  if (downState == GPIO_PIN_RESET && lastdownState == GPIO_PIN_SET) {
			  temp_set -= 1;
			  if (temp_set < temp_set_min) temp_set = temp_set_min;
			  LCD_Clear();
			  LCD_Write(" SET TEMP MODE", 1);
			  sprintf(lcd_str, "New set temp: %.0f", temp_set);
			  LCD_Write(lcd_str, 2);
			  HAL_Delay(50);
		  }
		  lastdownState = downState;

	  } else {
		  // Main Display
		  temp = DS18b20_temp();
		  if (temp >= temp_set){
			  fan_state = 1;
			  sprintf(lcd_str, " %.0f    %.0f    ON\r\n", temp, temp_set);
		  } else {
			  fan_state = 0;
			  sprintf(lcd_str, " %.0f    %.0f    OFF\r\n", temp, temp_set);
		  }
		  HAL_GPIO_WritePin(FAN_GPIO_Port, FAN_Pin, fan_state);
		  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, fan_state);

		  LCD_Clear();
		  LCD_Write("TEMP   SET   FAN", 1);
		  LCD_Write(lcd_str, 2);
		  HAL_Delay(50);
	  }

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_Pin|ONEWIRE_Pin|FAN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_Pin ONEWIRE_Pin FAN_Pin */
  GPIO_InitStruct.Pin = LED_Pin|ONEWIRE_Pin|FAN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SET_Pin UP_Pin DOWN_Pin */
  GPIO_InitStruct.Pin = SET_Pin|UP_Pin|DOWN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB3 PB4 PB5
                           PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
  __disable_irq();
  while (1)
  {
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
