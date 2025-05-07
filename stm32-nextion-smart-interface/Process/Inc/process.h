#ifndef __PROCESS_H_
#define __PROCESS_H_

#include "stm32g4xx_hal.h"
#include "main.h"
#include "M24C64.h"
#include "PCF85063.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "packetreceive.h"
#include "uart_configuration.h"
#include "nextion.h"
#include "stm32g4xx_it.h"
#include "delay_handler.h"


void process_INIT(void);
void Process_Nextion(void);
void Prosess_PacketComminication(void);

nextion_page_state_t get_nextion_page_state(void);





#endif