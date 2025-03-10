/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
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
uint16_t leds[] = { GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15 };  // LED PİNLERİNİ AYARLADIK
int kesmeBayrak = 0;       // KESMEYİ KONTROL EDER
int i;                     // FOR DÖNGÜSÜNDE KULLANILAN INT DEĞERİ
int butonSayac = 0;        // BUTONA KAÇ DEFA BASTIĞIMIZI SAYAR
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
int main(void) {

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

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_15, 1);  // 12 VE 15. PİNLERİ AKTİF ETTİK (ANA PROGRAM)

		if (kesmeBayrak) {  //KESME BAYRAĞI KONTROL EDİLİR 1 İSE İÇERİ GİRER.
			kesmeBayrak = 0;  //KESME BAYRAĞINI SIFIRLIYORUZ BİR SONRAKİNDE DÜZGÜNCE ÇALIŞMASI İÇİN

			/*
			 // BURADA BUTONA TIKLADIĞIMIZDA 14 VE 15 PİNLERİ AKTİF EDİYOR 12 Yİ KAPATIYOR ***
			 //  DAHA SONRA 2 SANİYE BEKLEDİĞİNDE 14 Ü KAPATIYOR VE KESMEDEN ÇIKIYOR.   ***

			 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14 | GPIO_PIN_15, 1);
			 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 0);
			 HAL_Delay(2000);
			 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 0);

			 */

			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_15, 0);   // AÇIK OLAN LEDLERİ KAPADIK
			HAL_Delay(1000);   // 1 SANİYE BEKLEDİK

			if (butonSayac == 1) {  // BUTON 1 KERE BASILDIYSA BU FONKSİYONA GİRER

				for (i = 0; i < 4; ++i) {
					HAL_GPIO_WritePin(GPIOD, leds[i], 1);
					HAL_Delay(200);
				}
				for (i = 0; i < 4; ++i) {
					HAL_GPIO_WritePin(GPIOD, leds[i], 0);
					HAL_Delay(200);

				}
			} else if (butonSayac == 2) {   // BUTON 2 KERE BASILDIYSA BU FONKSİYONA GİRER
				HAL_Delay(200);
				for (i = 3; i >= 0; --i) {
					HAL_GPIO_WritePin(GPIOD, leds[i], 1);
					HAL_Delay(200);
				}
				HAL_GPIO_WritePin(GPIOD,
				GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, 0);
				HAL_Delay(100);
			}
			else if (butonSayac >= 3) {    // BUTON 3 KERE VE DAHA ÜSTÜ BASILDIĞINDA BİR ŞEY YAPMAYIP KESMEDEN ÇIKMASINI SAĞLAR

			}

			butonSayac = 0 ;  // KESMEDEN ÇIKMADAN ÖNCE BUTON SAYACI 0 LIYORUZ ÇÜNKÜ BUTONA TEKRAR BASILDIĞINDA 1 DEN BAŞLAMASINI İSTİYORUZ.
		}

	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 50;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */

	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOD,
	GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);

	/*Configure GPIO pin : PA0 */
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PD12 PD13 PD14 PD15 */
	GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	/* USER CODE BEGIN MX_GPIO_Init_2 */

	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {   // BUTONA BASILDIĞINDA ÇAĞIRILIR.

	if (GPIO_Pin == GPIO_PIN_0) {                  //BUTONA PA0 DAN MI BASILDI KONTROL EDİLİR.
		kesmeBayrak = 1;                           //KESME BAYRAK DURUMUNU 1 YAPAR
		butonSayac++;                              //BUTON SAYICINI BASTIKÇA ARTMASINI SAĞLAR

	}

}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
