#ifndef _EE24_H_
#define _EE24_H_

/***********************************************************************************************************

  Author:     Nima Askari
  Github:     https://www.github.com/NimaLTD
  LinkedIn:   https://www.linkedin.com/in/nimaltd
  Youtube:    https://www.youtube.com/@nimaltd
  Instagram:  https://instagram.com/github.NimaLTD

  Version:    3.2.0

  History:
              3.2.0
              - Added ThreadX Configuration

              3.1.0
              - Added WP pin control
              - Fix 1Kb and 2Kb memory writing

              3.0.1
              - Fixed Address
                        
              3.0.0
              - Rewrite again
              - Support STM32CubeMx Packet installer

***********************************************************************************************************/



/************************************************************************************************************
**************    Include Headers
************************************************************************************************************/

#include <stdbool.h>
#include "main.h"


/************************************************************************************************************
**************    Public Definitions
************************************************************************************************************/

#define EE24_ADDRESS_DEFAULT 0xA0

// #define EE24_SIZE            64

// #define EE24_1KBIT              1
// #define EE24_2KBIT              2
// #define EE24_4KBIT              4
// #define EE24_8KBIT              8
// #define EE24_16KBIT             16
#define EE24_1KBIT                            1
#define EE24_2KBIT                            2
#define EE24_4KBIT                            4
#define EE24_8KBIT                            8
#define EE24_16KBIT                           16
#define EE24_32KBIT                           32
#define EE24_64KBIT                           64
#define EE24_128KBIT                          128
#define EE24_256KBIT                          256
#define EE24_512KBIT                          512

#define EE24_RTOS_DISABLE                     0
#define EE24_RTOS_CMSIS_V1                    1
#define EE24_RTOS_CMSIS_V2                    2
#define EE24_RTOS_THREADX                     3

/**
	MiddleWare name : NimaLTD.I-CUBE-EE24.3.2.0
	MiddleWare fileName : ./NimaLTD.I-CUBE-EE24_conf.h
*/
/*---------- EE24_SIZE  -----------*/
#define EE24_SIZE      64

/*---------- EE24_RTOS  -----------*/
#define EE24_RTOS      EE24_RTOS_DISABLE

/*---------- EE24_USE_WP_PIN  -----------*/
#define EE24_USE_WP_PIN      true



/************************************************************************************************************
**************    Public struct/enum
************************************************************************************************************/

typedef struct
{
  I2C_HandleTypeDef      *HI2c;
  uint8_t                Address;
  uint8_t                Lock;
#if EE24_USE_WP_PIN == true
  GPIO_TypeDef           *WpGpio;
  uint16_t                WpPin;
#endif

} EE24_HandleTypeDef;

/************************************************************************************************************
**************    Public Functions
************************************************************************************************************/

#if EE24_USE_WP_PIN == false
bool EE24_Init(EE24_HandleTypeDef *Handle, I2C_HandleTypeDef *HI2c, uint8_t I2CAddress);
#else
bool EE24_Init(EE24_HandleTypeDef *Handle, I2C_HandleTypeDef *HI2c, uint8_t I2CAddress, GPIO_TypeDef *WpGpio, uint16_t WpPin);
#endif
bool EE24_Read(EE24_HandleTypeDef *Handle, uint32_t Address, uint8_t *Data, size_t Len, uint32_t Timeout);
bool EE24_Write(EE24_HandleTypeDef *Handle, uint32_t Address, uint8_t *Data, size_t Len, uint32_t Timeout);

#ifdef __cplusplus
}
#endif
#endif