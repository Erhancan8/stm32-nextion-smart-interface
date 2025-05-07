#include "delay_handler.h"


static uint32_t hmsCnt = 0;

void delay_init(void) {
	SystemCoreClockUpdate();
	
	//SystemCoreClock / 1000
	if(SysTick_Config(CLOCK_FREQUENCY)){
		while(1); //Error setting SysTick.
	}
}

uint8_t delay_tick_1ms(uint32_t *last, uint32_t ticks) {
	if((uint32_t)(HAL_GetTick() - *last) >= ticks)
	{
		*last = HAL_GetTick();
		return 1;
	}

	return 0;
}

uint8_t delay_tick_100ms(uint32_t *last, uint32_t ticks) {
	static uint32_t _u32_ms_tick = 0;

	if(delay_tick_1ms(&_u32_ms_tick,99))
		hmsCnt++;

	if((uint32_t)(hmsCnt - *last) >= ticks)
	{
		*last = hmsCnt;
		return 1;
	}

	return 0;
}

uint8_t delay_tick_1ms_no_rst(uint32_t *last, uint32_t ticks) {
	if((uint32_t)(HAL_GetTick() - *last) >= ticks)
	{
		return 1;
	}

	return 0;
}

uint8_t delay_tick_100ms_no_rst(uint32_t *last, uint32_t ticks) {
	static uint32_t _u32_ms_tick = 0;

	if(delay_tick_1ms_no_rst(&_u32_ms_tick,99))
		hmsCnt++;

	if((uint32_t)(hmsCnt - *last) >= ticks)
	{
		*last = hmsCnt;
		return 1;
	}

	return 0;
}




