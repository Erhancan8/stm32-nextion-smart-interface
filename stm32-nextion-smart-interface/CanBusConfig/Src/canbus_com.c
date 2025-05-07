#include "canbus_com.h"


static FDCAN_TxHeaderTypeDef st_canbus_TxTransmiter;
static FDCAN_RxHeaderTypeDef st_canbus_RxReceiver;
static FDCAN_FilterTypeDef   st_canbus_FilterConfig;




st_canbus_function_typeDef canbus_function_typeDef = {  CANBUS_TX_INIT, 
                                                        CANBUS_FILTER_INIT,
                                                        CANBUS_RX0_IRQHandler,
                                                        CANBUS_TX0,
                                                        CANBUS_change_indentifier,
};







void CANBUS_TX_INIT( FDCAN_HandleTypeDef* hfdcan1, uint32_t indentifier, uint32_t datalenght)
{

    st_canbus_TxTransmiter.Identifier           = indentifier; 
    st_canbus_TxTransmiter.IdType               = FDCAN_STANDARD_ID;
    st_canbus_TxTransmiter.TxFrameType          = FDCAN_DATA_FRAME;   //Veri çerçevesi. veya   FDCAN_REMOTE_FRAME: Uzaktan çerçeve. eğer veri alacaksak uzaktan. data vereceksek veri çervevesi olmalı
    st_canbus_TxTransmiter.DataLength           = datalenght;         //Gönderilecek çerçevenin veri uzunluğunu belirtir.
    st_canbus_TxTransmiter.ErrorStateIndicator  = FDCAN_ESI_ACTIVE;   // hata durumu aktif veya pasif
    st_canbus_TxTransmiter.BitRateSwitch        = FDCAN_BRS_OFF;      //Bu alan, bit hızının değiştirilip değiştirilmediğini belirtir.
    st_canbus_TxTransmiter.FDFormat             = FDCAN_FD_CAN;       //Mesajın klasik CAN formatında mı yoksa FD (Flexible Data) formatında mı gönderileceğini belirtir.
    st_canbus_TxTransmiter.TxEventFifoControl   = FDCAN_NO_TX_EVENTS;
    st_canbus_TxTransmiter.MessageMarker        = 0;
}

void CANBUS_FILTER_INIT( FDCAN_HandleTypeDef* hfdcan1, uint32_t filterid1, uint32_t filterid2)
{

st_canbus_FilterConfig.IdType               = FDCAN_STANDARD_ID;
st_canbus_FilterConfig.FilterIndex          = 0; 
st_canbus_FilterConfig.FilterType           = FDCAN_FILTER_MASK; 
st_canbus_FilterConfig.FilterConfig         = FDCAN_FILTER_TO_RXFIFO0;
st_canbus_FilterConfig.FilterID1            = 0x321; // FİLTER
st_canbus_FilterConfig.FilterID2            = 0x7FF; // MASK


    HAL_FDCAN_ConfigFilter(hfdcan1, &st_canbus_FilterConfig);
    HAL_FDCAN_Start(hfdcan1);
    
    if(HAL_FDCAN_ActivateNotification(hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0)!= HAL_OK)
    {
        Error_Handler();
    } //kesmede kullanılır
}


void CANBUS_RX0_IRQHandler( FDCAN_HandleTypeDef* hfdcan1, uint8_t* CanBus_Buffer_RxReceive)
{
  if (HAL_FDCAN_GetRxMessage( hfdcan1, FDCAN_RX_FIFO0, &st_canbus_RxReceiver, CanBus_Buffer_RxReceive) != HAL_OK)
  {
    Error_Handler();
  }

  if(HAL_FDCAN_AddMessageToTxFifoQ(hfdcan1, &st_canbus_RxReceiver,  CanBus_Buffer_RxReceive) != HAL_OK)
  {
    Error_Handler();
  }
}


void CANBUS_TX0( FDCAN_HandleTypeDef* hfdcan1, const uint8_t* CanBus_Buffer_TxSend)
{
  if (HAL_FDCAN_AddMessageToTxFifoQ(hfdcan1, &st_canbus_TxTransmiter, CanBus_Buffer_TxSend) != HAL_OK)
  {
      Error_Handler();
  }
}

void CANBUS_change_indentifier(uint32_t indentifier)
{
    st_canbus_TxTransmiter.Identifier = indentifier; 
}