#ifndef NEXTION_H
#define NEXTION_H

#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define RxBufferSize 50
#define NEXTION_RX_BUFFER_SIZE      50

#define Nextion_TouchEvent          0x65
#define Nextion_Page0               0x00 
#define Nextion_Page1               0x01
#define Nextion_Page2               0x02
#define Nextion_Page3               0x03
#define Nextion_Page4               0x04
#define Nextion_Page5               0x05
#define Nextion_Page6               0x06
#define Nextion_EventRelease        0x00
#define Nextion_EventPress          0x01
#define NEXTION_COPMPONENT_ID_RESET 0X00


typedef enum{
    _Nextion_componentId0,
    _Nextion_componentId1,
    _Nextion_componentId2,
    _Nextion_componentId3,
    _Nextion_componentId4,
    _Nextion_componentId5,
    _Nextion_componentId6,
    _Nextion_componentId7,
    _Nextion_componentId8,
    _Nextion_componentId9,
    _Nextion_componentIdA,
    _Nextion_componentIdB,
    _Nextion_componentIdC,
    _Nextion_componentIdD,
    _Nextion_componentIdE,
    _Nextion_componentIdF
}_NEXTION_COMPONENTID;

typedef enum _nextion_page_state_t{
  NEXTION_PAGE0,
  NEXTION_PAGE1,
  NEXTION_PAGE2,
  NEXTION_PAGE3,
  NEXTION_PAGE4,
}nextion_page_state_t;

typedef struct{
    uint8_t TouchEvent;
    nextion_page_state_t pageNumber;
    uint8_t componendId;
    uint8_t event;
    uint8_t dataEnd_light[3];
}NEXTION_PackageTypeDef;




void NEXTION_init(void);
void NEXTION_SendString(char* ID, char* string);
void NEXTION_SendValue(char* ID, char* string);
void NEXTION_SendPage(char* page_number);
void NEXTION_SendCode(char* string);
nextion_page_state_t get_nextion_page_state(void);





#endif /* NEXTION_H */
