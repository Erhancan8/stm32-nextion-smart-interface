/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

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
void serial_message(const char *serial_data, ...);
I2C_HandleTypeDef* get_pointer_hi2c2(void);
UART_HandleTypeDef* get_pointer_huart1(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MCU_BQ_UART_TX__3V3_Pin GPIO_PIN_4
#define MCU_BQ_UART_TX__3V3_GPIO_Port GPIOC
#define MCU_BQ_UART_RX__3V3_Pin GPIO_PIN_5
#define MCU_BQ_UART_RX__3V3_GPIO_Port GPIOC
#define RED_LED_Pin GPIO_PIN_0
#define RED_LED_GPIO_Port GPIOB
#define GREEN_LED_Pin GPIO_PIN_1
#define GREEN_LED_GPIO_Port GPIOB
#define BLUE_LED_Pin GPIO_PIN_2
#define BLUE_LED_GPIO_Port GPIOB
#define MCU_BUZZER__3V3_Pin GPIO_PIN_10
#define MCU_BUZZER__3V3_GPIO_Port GPIOB
#define MCU_SPI2_SDCARD_CS__3V3_Pin GPIO_PIN_12
#define MCU_SPI2_SDCARD_CS__3V3_GPIO_Port GPIOB
#define MCU_SPI2_CLK__3V3_Pin GPIO_PIN_13
#define MCU_SPI2_CLK__3V3_GPIO_Port GPIOB
#define MCU_SPI2_MISO__3V3_Pin GPIO_PIN_14
#define MCU_SPI2_MISO__3V3_GPIO_Port GPIOB
#define MCU_SPI2_MOSI__3V3_Pin GPIO_PIN_15
#define MCU_SPI2_MOSI__3V3_GPIO_Port GPIOB
#define MCU_I2C_SDA__3V3_Pin GPIO_PIN_8
#define MCU_I2C_SDA__3V3_GPIO_Port GPIOA
#define MCU_I2C_SCL__3V3_Pin GPIO_PIN_9
#define MCU_I2C_SCL__3V3_GPIO_Port GPIOA
#define MCU_SWDIO__3V3_Pin GPIO_PIN_13
#define MCU_SWDIO__3V3_GPIO_Port GPIOA
#define MCU_SWCLK__3V3_Pin GPIO_PIN_14
#define MCU_SWCLK__3V3_GPIO_Port GPIOA
#define MCU_EEPROM_WC__3V3_Pin GPIO_PIN_15
#define MCU_EEPROM_WC__3V3_GPIO_Port GPIOA
#define MCU_USART3_RX__3V3_Pin GPIO_PIN_11
#define MCU_USART3_RX__3V3_GPIO_Port GPIOC
#define MCU_USART3_TX__3V3_Pin GPIO_PIN_9
#define MCU_USART3_TX__3V3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define SERIAL_UART_ADDR      &huart3
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
