

#include "PCF85063.h"

static datetime_t st_datetime;


static uint8_t decToBcd(int val);
static int bcdToDec(uint8_t val);

I2C_HandleTypeDef *_pcf850_i2c;


void PCF85_Init(I2C_HandleTypeDef *_hi2c)
{
	_pcf850_i2c = _hi2c;
  
	// Initiate Normal Mode, RTC Run, NO reset, No correction, , 24hr format, Internal load capacitane 12.5pf

	uint8_t PCFINIT_ = 0x49;
    HAL_I2C_Mem_Write(_pcf850_i2c, I2C_ADDR, REG_CTRL1_ADDR ,1, &PCFINIT_, 1, 1000 );
  
}


void PCF85_Reset(){

	uint8_t PCFIRSTS_ = 0x59;
	HAL_I2C_Mem_Write(_pcf850_i2c, I2C_ADDR, REG_CTRL1_ADDR ,1, &PCFIRSTS_, 1, 1000 );
    
}

			//SET FONKSİYONLARI

void PCF85_SetTime(uint8_t hour, uint8_t minute, uint8_t second){
	uint8_t buf[3] = {decToBcd(second),
						decToBcd(minute),
							decToBcd(hour)};
	HAL_I2C_Mem_Write(_pcf850_i2c, I2C_ADDR,REG_TIME_ADDR,1, buf, 3, 1000 );
}

void PCF85_SetDate(uint8_t weekday, uint8_t day, uint8_t month, uint16_t yr){
	uint8_t buf[4] = {decToBcd(day),
			decToBcd(weekday),
			decToBcd(month),
			decToBcd(yr-YEAR_OFFSET)};

	HAL_I2C_Mem_Write(_pcf850_i2c, I2C_ADDR,REG_DATE_ADDR,1, buf, 4, 1000 );
}

void PCF85_SetSecond(uint8_t second)
{
	uint8_t buf[1] = {decToBcd(second)};
	HAL_I2C_Mem_Write(_pcf850_i2c, I2C_ADDR,REG_TIME_ADDR,1, buf, 1, 1000 );
}
void PCF85_SetMinute(uint8_t minute)
{
	uint8_t buf[1] = {decToBcd(minute)};
	HAL_I2C_Mem_Write(_pcf850_i2c, I2C_ADDR,REG_MIN_ADDR,1, buf, 1, 1000 );
}

void PCF85_SetHour(uint8_t hour)
{
	uint8_t buf[1] = {decToBcd(hour)};
	HAL_I2C_Mem_Write(_pcf850_i2c, I2C_ADDR,REG_HOUR_ADRR,1, buf, 1, 1000 );
}

void PCF85_Setweekday(uint8_t weekday)
{
	uint8_t buf[1] = {decToBcd(weekday)};
	HAL_I2C_Mem_Write(_pcf850_i2c, I2C_ADDR,REG_WEEKDAY_ADRR,1, buf, 1, 1000 );
}

void PCF85_Setday(uint8_t day)
{
	uint8_t buf[1] = {decToBcd(day)};
	HAL_I2C_Mem_Write(_pcf850_i2c, I2C_ADDR,REG_DAY_ADRR,1, buf, 1, 1000 );
}

void PCF85_Setmonth(uint8_t month)
{
	uint8_t buf[1] = {decToBcd(month)};
	HAL_I2C_Mem_Write(_pcf850_i2c, I2C_ADDR,REG_MONTH_ADRR,1, buf, 1, 1000 );	
}

void PCF85_Setyear(uint16_t yr)
{
	uint8_t buf[1] = {decToBcd(yr)};
	HAL_I2C_Mem_Write(_pcf850_i2c, I2C_ADDR,REG_YEAR_ADRR,1, buf, 1, 1000 );	
}
					//GET FONKSİYONLARI
uint8_t PCF85_GetDateTime(uint8_t *buf){
	uint8_t bufss[7] = {0};

	if(HAL_I2C_Mem_Read(_pcf850_i2c, I2C_ADDR, REG_TIME_ADDR, 1, bufss, 7, 1000 ) == HAL_OK){

		buf[0] = bcdToDec(bufss[0] & 0x7F);
		buf[1] = bcdToDec(bufss[1] & 0x7F);
		buf[2] = bcdToDec(bufss[2] & 0x3F);
		buf[3] = bcdToDec(bufss[3] & 0x3F);
		buf[4] = bcdToDec(bufss[4] & 0x07);
		buf[5] = bcdToDec(bufss[5] & 0x1F);
		buf[6] = bcdToDec(bufss[6]);

		return 1;
	}
  return 0;
}
uint8_t PCF85_GetSecond(void)
{
	uint8_t _retValArr = 0;
	HAL_I2C_Mem_Read(_pcf850_i2c, I2C_ADDR, REG_TIME_ADDR, 1, &_retValArr, 1, 1000 );
	return 	bcdToDec(_retValArr & 0x7F);
}
uint8_t PCF85_GetMinute(void)
{
	uint8_t _retValArr = 0;
	HAL_I2C_Mem_Read(_pcf850_i2c, I2C_ADDR, REG_MIN_ADDR, 1, &_retValArr, 1, 1000 );
	return 	bcdToDec(_retValArr & 0x7F);
}
uint8_t PCF85_GetHour(void)
{
	uint8_t _retValArr = 0;
	HAL_I2C_Mem_Read(_pcf850_i2c, I2C_ADDR, REG_HOUR_ADRR , 1, &_retValArr, 1, 1000 );
	return 	bcdToDec(_retValArr & 0x3F);
}
uint8_t PCF85_Getweekday(void)
{
	uint8_t _retValArr = 0;
	HAL_I2C_Mem_Read(_pcf850_i2c, I2C_ADDR, REG_WEEKDAY_ADRR, 1, &_retValArr, 1, 1000 );
	return 	bcdToDec(_retValArr & 0x07);
}
uint8_t PCF85_Getday(void)
{
	uint8_t _retValArr = 0;
	HAL_I2C_Mem_Read(_pcf850_i2c, I2C_ADDR, REG_DAY_ADRR, 1, &_retValArr, 1, 1000 );
	return bcdToDec(_retValArr & 0x3F);
}
uint8_t PCF85_Getmonth(void)
{
	uint8_t _retValArr = 0;
	HAL_I2C_Mem_Read(_pcf850_i2c, I2C_ADDR, REG_MONTH_ADRR, 1, &_retValArr, 1, 1000 );
	return 	bcdToDec(_retValArr & 0x1F);
}
uint16_t PCF85_Getyear(void)
{
	uint8_t _retValArr = 0;
	HAL_I2C_Mem_Read(_pcf850_i2c, I2C_ADDR, REG_YEAR_ADRR, 1, &_retValArr, 1, 1000 );
	return 	bcdToDec(_retValArr)+YEAR_OFFSET;
}

// Convert normal decimal numbers to binary coded decimal
static uint8_t decToBcd(int val){
  return (uint8_t)( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
static int bcdToDec(uint8_t val){
  return (int)( (val/16*10) + (val%16) );
}


void PCF85_task(void) {
	uint8_t bufss[7] = {0};
	if(HAL_I2C_Mem_Read(_pcf850_i2c, I2C_ADDR, REG_TIME_ADDR, 1, bufss, 7, 1000 ) == HAL_OK){

		st_datetime.st_time.second = bcdToDec(bufss[0] & 0x7F);
		st_datetime.st_time.minute = bcdToDec(bufss[1] & 0x7F);
		st_datetime.st_time.hour = bcdToDec(bufss[2] & 0x3F);
		st_datetime.st_date.day = bcdToDec(bufss[3] & 0x3F);
		st_datetime.weekday = bcdToDec(bufss[4] & 0x07);
		st_datetime.st_date.month = bcdToDec(bufss[5] & 0x1F);
		st_datetime.st_date.yr = bcdToDec(bufss[6])+YEAR_OFFSET;
				
	}
}

time_t get_time(void)
{
	return st_datetime.st_time;
}
date_t get_date(void)
{
	return st_datetime.st_date;
}
