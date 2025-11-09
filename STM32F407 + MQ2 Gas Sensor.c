/* USER CODE BEGIN Header */
 /** ******************************************************************************
 * @file
 * @brief
 : main.c
 : MQ2 Gas Sensor (Analog A0) + Buzzer with STM32F407
 ******************************************************************************
 */
 /* USER CODE END Header */
 #include "main.h"
 #include <stdio.h>
 /* Private variables---------------------------------------------------------*/
 ADC_HandleTypeDef hadc1;
 /* Function Prototypes */
 void SystemClock_Config(void);
 static void MX_GPIO_Init(void);
 static void MX_ADC1_Init(void);
 int main(void)
 {
HAL_Init();
 SystemClock_Config();
 MX_GPIO_Init();
 MX_ADC1_Init();
 uint32_t gas_value = 0;
 const uint32_t threshold = 2000; // adjust based on testing
 while (1)
 {
HAL_ADC_Start(&hadc1);
 HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
 gas_value = HAL_ADC_GetValue(&hadc1);
 if (gas_value > threshold)
 {
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET); // buzzer ON
 } else
 {
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET); // buzzer OFF
 }
 HAL_Delay(300);
 }
 }
 /* ADC1 init */
 static void MX_ADC1_Init(void)
 {
ADC_ChannelConfTypeDef sConfig = {0};
 __HAL_RCC_ADC1_CLK_ENABLE();
 hadc1.Instance = ADC1;
 hadc1.Init.Resolution = ADC_RESOLUTION_12B;
 hadc1.Init.ScanConvMode = DISABLE;
 hadc1.Init.ContinuousConvMode = DISABLE;
 hadc1.Init.DiscontinuousConvMode = DISABLE;
 hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
 HAL_ADC_Init(&hadc1);
 sConfig.Channel = ADC_CHANNEL_0; // PA0
 sConfig.Rank = 1;
 sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
 HAL_ADC_ConfigChannel(&hadc1, &sConfig);
 }
 /* GPIO init */
 static void MX_GPIO_Init(void)
 {
GPIO_InitTypeDef GPIO_InitStruct = {0};
 __HAL_RCC_GPIOD_CLK_ENABLE();
 // Buzzer pin (PD11)
 GPIO_InitStruct.Pin = GPIO_PIN_11;
 GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
 GPIO_InitStruct.Pull = GPIO_NOPULL;
 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
 HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
 }
 /* Clock Config (same as before) */
 void SystemClock_Config(void)
 {
RCC_OscInitTypeDef RCC_OscInitStruct = {0};
 RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
 __HAL_RCC_PWR_CLK_ENABLE();
 __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
 RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
 RCC_OscInitStruct.HSIState = RCC_HSI_ON;
 RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
 RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
 RCC_OscInitStruct.PLL.PLLM = 16;
 RCC_OscInitStruct.PLL.PLLN = 336;
 RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
 RCC_OscInitStruct.PLL.PLLQ = 7;
 HAL_RCC_OscConfig(&RCC_OscInitStruct);
 RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
 |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
 RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
 RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
 RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
 RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
 HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
 }
 /* Error Handler */
 void Error_Handler(void)
 {
__disable_irq();
}
