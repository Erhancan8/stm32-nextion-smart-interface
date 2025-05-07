#include "uart_configuration.h"
#include "process.h"

static NEXTION_PackageTypeDef st_nextion_package;
extern UART_HandleTypeDef   huart3;
extern DMA_HandleTypeDef    hdma_usart3_rx;

extern DMA_HandleTypeDef    hdma_usart1_rx;
extern UART_HandleTypeDef   huart1;

static uint8_t RxBuf[RXBUF_SIZE];
uint8_t rxbuffer_uart1 [7];

 uint16_t oldPos = 0;
 uint16_t newPos = 0;

uint8_t MainBuf[MainBuf_SIZE];

volatile int uart_dma_flag  = 0;
volatile int NEXTION_DMA_FLAG = 0;
int update_st_nextion_package_flag = 0;


void UartDmaInit(void)
{
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, RxBuf, RXBUF_SIZE);
  __HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);

    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t *) rxbuffer_uart1, RXBUF_SIZE);
  __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  if (huart->Instance == USART3)
  {
    uart_dma_flag = DMA_FLAG_ENABLE;
    oldPos = newPos;

    memcpy ((uint8_t *)MainBuf+oldPos, RxBuf, Size);
      

    newPos = Size+oldPos;

    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, (uint8_t *) RxBuf, RXBUF_SIZE);
    __HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);

    
  }

  if(huart->Instance == USART1)
  {
    // serial_message(" [[%d",rxbuffer_uart1[0]);
    // serial_message(" %d",rxbuffer_uart1[1]);
    // serial_message(" %d",rxbuffer_uart1[2]);
    // serial_message(" %d",rxbuffer_uart1[3]);
    // serial_message(" %d",rxbuffer_uart1[4]);
    // serial_message(" %d",rxbuffer_uart1[5]);
    // serial_message(" %d-----]\n",rxbuffer_uart1[6]);
    
    // if(NEXTION_DMA_FLAG == DMA_FLAG_DISABLE)
    // {

    NEXTION_DMA_FLAG = DMA_FLAG_ENABLE;
    //update_st_nextion_package_flag = 1;
  
     memcpy(&st_nextion_package, rxbuffer_uart1, sizeof rxbuffer_uart1);



  		for(int i=Size ; i<10; i++)
      {
			  rxbuffer_uart1[i] = 0;
		  }

    // }
      HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t *) rxbuffer_uart1, RXBUF_SIZE);
      __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);

      
  }
}

NEXTION_PackageTypeDef get_st_nextion_package(void)
{
  return st_nextion_package;
}