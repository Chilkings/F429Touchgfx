/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

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
#define IIC_SDA_Pin GPIO_PIN_8
#define IIC_SDA_GPIO_Port GPIOI
#define LED4_Pin GPIO_PIN_13
#define LED4_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_14
#define LED3_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_15
#define LED2_GPIO_Port GPIOC
#define Key3_Pin GPIO_PIN_11
#define Key3_GPIO_Port GPIOI
#define W25QXX_CS_Pin GPIO_PIN_6
#define W25QXX_CS_GPIO_Port GPIOF
#define Down_Key_Pin GPIO_PIN_1
#define Down_Key_GPIO_Port GPIOC
#define AIIC_SCL_Pin GPIO_PIN_1
#define AIIC_SCL_GPIO_Port GPIOA
#define T_RST_Pin GPIO_PIN_2
#define T_RST_GPIO_Port GPIOA
#define TFT_I2C_SCL_Pin GPIO_PIN_2
#define TFT_I2C_SCL_GPIO_Port GPIOH
#define T_INT_Pin GPIO_PIN_3
#define T_INT_GPIO_Port GPIOH
#define T_INT_EXTI_IRQn EXTI3_IRQn
#define LCD_BL_Pin GPIO_PIN_7
#define LCD_BL_GPIO_Port GPIOA
#define Magnet_Pin GPIO_PIN_5
#define Magnet_GPIO_Port GPIOC
#define TFT_I2C_SDA_Pin GPIO_PIN_6
#define TFT_I2C_SDA_GPIO_Port GPIOH
#define Key4_Pin GPIO_PIN_7
#define Key4_GPIO_Port GPIOH
#define T_RSTH8_Pin GPIO_PIN_8
#define T_RSTH8_GPIO_Port GPIOH
#define MPU_SDA_Pin GPIO_PIN_13
#define MPU_SDA_GPIO_Port GPIOB
#define MPU_SCL_Pin GPIO_PIN_14
#define MPU_SCL_GPIO_Port GPIOB
#define AIIC_SDA_Pin GPIO_PIN_15
#define AIIC_SDA_GPIO_Port GPIOB
#define LED5_Pin GPIO_PIN_11
#define LED5_GPIO_Port GPIOD
#define Iot_Reset_Pin GPIO_PIN_12
#define Iot_Reset_GPIO_Port GPIOD
#define IOTpower_Pin GPIO_PIN_13
#define IOTpower_GPIO_Port GPIOD
#define LCD_DISP_Pin GPIO_PIN_8
#define LCD_DISP_GPIO_Port GPIOA
#define IIC_SCL_Pin GPIO_PIN_3
#define IIC_SCL_GPIO_Port GPIOI
#define Buzzer_Pin GPIO_PIN_3
#define Buzzer_GPIO_Port GPIOD
#define Key2_Pin GPIO_PIN_14
#define Key2_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
