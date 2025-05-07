#include "nextion.h"


static uint8_t Cmd_End[3] = {0xff, 0xff, 0xff};



void NEXTION_SendCode(char* string)
{
    char buf[50];
    int len = sprintf(buf, "%s", string);
    HAL_UART_Transmit(get_pointer_huart1(), (uint8_t*) buf, len, 1000);
    HAL_UART_Transmit(get_pointer_huart1(), Cmd_End, 3, 1000);
}

void NEXTION_SendString(char* ID, char* string)
{
    char buf[50];
    int len = sprintf(buf, "%s.txt=\"%s\"",ID, string);
    HAL_UART_Transmit(get_pointer_huart1(), (uint8_t*) buf, len, 1000);
    HAL_UART_Transmit(get_pointer_huart1(), Cmd_End, 3, 1000);
}

void NEXTION_SendValue(char* ID, char* string)
{
    char buf[50];
    int len = sprintf(buf, "%s.val=%s",ID, string);
    HAL_UART_Transmit(get_pointer_huart1(), (uint8_t*) buf, len, 1000);
    HAL_UART_Transmit(get_pointer_huart1(), Cmd_End, 3, 1000);
}

void NEXTION_SendPage(char* page_number)
{
    char buf[50];
    int len = sprintf(buf, "page %s",page_number);
    HAL_UART_Transmit(get_pointer_huart1(), (uint8_t*) buf, len, 1000);
    HAL_UART_Transmit(get_pointer_huart1(), Cmd_End, 3, 1000);
}





