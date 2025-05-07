#ifndef _UART_CONFİGUARATİON_
#define _UART_CONFİGUARATİON_

#include "main.h"
#include <string.h>
#include "nextion.h"

#define RXBUF_SIZE     10
#define MainBuf_SIZE   128


typedef enum
{
  DMA_FLAG_DISABLE = 0U,
  DMA_FLAG_ENABLE
} DMA_FLAG_STATUS;


extern volatile int uart_dma_flag;
extern uint8_t MainBuf[MainBuf_SIZE];
extern uint16_t oldPos;
extern uint16_t newPos;
extern uint8_t rxbuffer_uart1 [];
extern volatile int NEXTION_DMA_FLAG ;
extern int   update_st_nextion_package_flag;


void UartDmaInit(void);
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);


NEXTION_PackageTypeDef get_st_nextion_package(void);






#endif