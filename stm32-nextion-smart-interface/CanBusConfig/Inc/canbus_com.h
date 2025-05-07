#ifndef __CANBUS_H_
#define __CANBUS_H_

#include "main.h"


#define MIN_ADDRES         ((uint32_t)0X10)
#define MAX_ADDRES         ((uint32_t)0x20)
#define INDENTIFIER        ((uint32_t)0x31)

typedef struct 
{
void (*canbus_tx_init_adr)              (FDCAN_HandleTypeDef*, uint32_t, uint32_t);
void (*canbus_filter_init_Adr)          (FDCAN_HandleTypeDef*, uint32_t, uint32_t);
void (*canbus_rx0_irqhandler_Adr)       (FDCAN_HandleTypeDef*, uint8_t*);
void (*canbus_tx0_adr)                  (FDCAN_HandleTypeDef*, const uint8_t*);
void (*canbus_change_indentifier_adr)   (uint32_t);
}st_canbus_function_typeDef;

extern st_canbus_function_typeDef canbus_function_typeDef;



void CANBUS_TX_INIT             ( FDCAN_HandleTypeDef* hfdcan1,       uint32_t indentifier, uint32_t datalenght);
void CANBUS_FILTER_INIT         ( FDCAN_HandleTypeDef* hfdcan1,       uint32_t filterid1,   uint32_t filterid2);
void CANBUS_RX0_IRQHandler      ( FDCAN_HandleTypeDef* hfdcan1,       uint8_t* CanBus_Buffer_RxReceive);
void CANBUS_TX0                 ( FDCAN_HandleTypeDef* hfdcan1, const uint8_t* CanBus_Buffer_TxSend);
void CANBUS_change_indentifier  ( uint32_t indentifier);





#endif