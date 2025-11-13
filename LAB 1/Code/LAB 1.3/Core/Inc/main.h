/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define W_Red_Pin GPIO_PIN_1
#define W_Red_GPIO_Port GPIOA
#define W_Yellow_Pin GPIO_PIN_2
#define W_Yellow_GPIO_Port GPIOA
#define W_Green_Pin GPIO_PIN_3
#define W_Green_GPIO_Port GPIOA
#define N_Red_Pin GPIO_PIN_4
#define N_Red_GPIO_Port GPIOA
#define N_Yellow_Pin GPIO_PIN_5
#define N_Yellow_GPIO_Port GPIOA
#define N_Green_Pin GPIO_PIN_6
#define N_Green_GPIO_Port GPIOA
#define E_Red_Pin GPIO_PIN_7
#define E_Red_GPIO_Port GPIOA
#define E_Yellow_Pin GPIO_PIN_8
#define E_Yellow_GPIO_Port GPIOA
#define E_Green_Pin GPIO_PIN_9
#define E_Green_GPIO_Port GPIOA
#define S_Red_Pin GPIO_PIN_10
#define S_Red_GPIO_Port GPIOA
#define S_Yellow_Pin GPIO_PIN_11
#define S_Yellow_GPIO_Port GPIOA
#define S_Green_Pin GPIO_PIN_12
#define S_Green_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
