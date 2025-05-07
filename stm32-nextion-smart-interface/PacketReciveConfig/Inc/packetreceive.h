#ifndef _COM_H
#define _COM_H

#include <stdint.h>
#include <string.h>
#include "main.h"
#include <stdlib.h>
#include <stdio.h>


#define START_STOP_BYTE       0x7E

typedef enum _packet_steps_t{
    PACKAGE_İS_VALİD,
    PACKAGE_START_BYTE,
    PACKAGE_LENGTH,
    PACKAGE_PAYLOUD,
    PACKAGE_CRC,
    PACKAGE_STOP_BYTE,
    PACKAGE_ENDING
}packet_steps_t;

typedef struct {
    uint8_t Start_byte;
    uint8_t Data_Lengh;
    uint8_t Payload[255];
    uint8_t CRC_byte[3];
    uint8_t Stop_byte;
}packet_data;

typedef packet_data (*func_ptr)(uint8_t*);




extern func_ptr function_ptr[];

int isPacketValid(uint8_t* data, uint8_t lenght);
packet_data getStartByte(uint8_t* data);
packet_data getLenght(uint8_t* data);
packet_data getPayloud(uint8_t* data);
packet_data getCrc (uint8_t* data);
packet_data getStopByte(uint8_t* data);

packet_steps_t get_packet_steps_state(void);
void set_packet_steps_state(packet_steps_t new_state);

void read_packet(void);




#endif