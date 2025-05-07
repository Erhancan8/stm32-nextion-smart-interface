#include "packetreceive.h"

static packet_data packetData;
static packet_steps_t packet_steps;

func_ptr function_ptr[] = { 
    NULL,
    getStartByte,
    getLenght,
    getPayloud,
    getCrc,
    getStopByte

};


int isPacketValid(uint8_t* data, uint8_t lenght)
{
    if(data[0] != START_STOP_BYTE)
    {
        serial_message("wrong start byte. start byte should be 0x7E");
        return 1;
    }
    if( memchr(data+1,START_STOP_BYTE,lenght) == NULL)
    {
        serial_message("wrong stop byte. stop byte should be 0x7E");
        return 1;

    }
    
    if(data[data[1] + 5] != START_STOP_BYTE)
    {
        serial_message("wrong lenght. lenght should be %d",data[1]+6);
         return 1;
    }
    return 0;
}

packet_data getStartByte(uint8_t* data)
{
    packetData.Start_byte = data[0];
    return packetData;
}

packet_data getLenght(uint8_t* data)
{
    packetData.Data_Lengh = data[1];
    return packetData;
}

packet_data getPayloud(uint8_t* data)
{
    memcpy(packetData.Payload, data+2, packetData.Data_Lengh);
    return packetData;
}

packet_data getCrc (uint8_t* data)
{
    memcpy(packetData.CRC_byte, data+2+packetData.Data_Lengh, 3);
    return packetData;
}

packet_data getStopByte(uint8_t* data)
{
    packetData.Stop_byte = data[5+packetData.Data_Lengh];
    return packetData;
}







packet_steps_t get_packet_steps_state(void) {
    return packet_steps;
}

void set_packet_steps_state(packet_steps_t new_state) {
    packet_steps = new_state;
}



void read_packet(void)
{
    serial_message("start byte:0x%02x\n ",packetData.Start_byte);
    for (size_t i = 0; i < packetData.Data_Lengh; i++)
    {
        serial_message("Payload:0x%02x ", packetData.Payload[i]);
    }
    serial_message("\n");
    for(size_t i=0 ; i<3; i++)
    {
        serial_message("CRC:0x%0x ",packetData.CRC_byte[i]);
    }
    serial_message("\n");
    serial_message("Stop byte:0x%02x \n",packetData.Stop_byte);
    serial_message("\n");
}



//      7E 01 C3 AC 31 83 7E 
//      7E 02 C1 AA BB 2A AB 7E
//      7E 03 C2 AA F1 AF 8A 40 7E
//      7E 04 C2 AA F1 F2 AF 8A 40 7E
//      7E 05 c3 C2 AA F1 F2 AF 8A 40 7E
//      7E 0a c1 c1 c1 c1 c1 C2 AA F1 F2 F5 AF 8A 40 7E

//      71 01 C3 AC 31 83 7E            7E 01 C3 AC 31 83 71        7E 01 C3 AC 31 83 71 7E
//      71 03 C2 AA F1 AF 8A 40 7E      7E 03 C2 AA F1 AF 8A 40 71  7E 03 C2 AA F1 AF 7E
//          start eror                  stop eror                   lenght eror

