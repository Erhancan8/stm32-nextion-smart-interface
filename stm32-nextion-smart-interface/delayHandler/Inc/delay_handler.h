

#ifndef INC_DELAY_HANDLER_H_
#define INC_DELAY_HANDLER_H_

#include "stdint.h"
#include "string.h"
#include "main.h"
#include "delay_handler_params.h"


void delay_init(void);
uint8_t delay_tick_1ms(uint32_t *last, uint32_t ticks);
uint8_t delay_tick_100ms(uint32_t *last, uint32_t ticks);
uint8_t delay_tick_1ms_no_rst(uint32_t *last, uint32_t ticks);
uint8_t delay_tick_100ms_no_rst(uint32_t *last, uint32_t ticks);


#endif /* INC_DELAY_HANDLER_H_ */
