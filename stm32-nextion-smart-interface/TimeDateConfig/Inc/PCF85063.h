/*
 * pcf85063a.h
 *
 *  Created on: 13 Aug. 2021
 *      Author: Zildjhan
 */

#ifndef INC_PCF85063A_H_
#define INC_PCF85063A_H_

#include "main.h"
#include <string.h>


#define REG_CTRL1_ADDR                   0x00
#define REG_CTRL2_ADDR                   0x01
#define REG_TIME_ADDR                    0x04
#define REG_DATE_ADDR                    0x07

#define I2C_ADDR                         0x51 << 1
#define YEAR_OFFSET						 1970

#define REG_SEC_ADDR                     0x04
#define REG_MIN_ADDR                     0x05
#define REG_HOUR_ADRR                    0x06
#define REG_WEEKDAY_ADRR                 0x08
#define REG_DAY_ADRR                     0x07
#define REG_MONTH_ADRR                   0x09
#define REG_YEAR_ADRR                    0x0A


typedef struct _time {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;   
}time_t;

typedef struct _date {
    uint8_t day;
    uint8_t month;
    uint16_t yr;
}date_t;

typedef struct{

    uint8_t weekday;
    time_t st_time;
    date_t st_date;

}datetime_t;




void PCF85_Init(I2C_HandleTypeDef *_hi2c);

void PCF85_Reset();

void PCF85_SetTime(uint8_t hour, uint8_t minute, uint8_t second);
void PCF85_SetDate(uint8_t weekday, uint8_t day, uint8_t month, uint16_t yr);

void PCF85_SetSecond(uint8_t second);
void PCF85_SetMinute(uint8_t minute);
void PCF85_SetHour(uint8_t hour);
void PCF85_Setweekday(uint8_t weekday);
void PCF85_Setday(uint8_t day);
void PCF85_Setmonth(uint8_t month);
void PCF85_Setyear(uint16_t yr);


uint8_t PCF85_GetDateTime(uint8_t *buf);

time_t get_time(void);
date_t get_date(void);
void PCF85_task(void);


uint8_t PCF85_GetSecond(void);
uint8_t PCF85_GetMinute(void);
uint8_t PCF85_GetHour(void);
uint8_t PCF85_Getweekday(void);
uint8_t PCF85_Getday(void);
uint8_t PCF85_Getmonth(void);
uint16_t PCF85_Getyear(void);



#endif /* INC_PCF85063A_H_ */

// weekday format
// 0 - sunday
// 1 - monday
// 2 - tuesday
// 3 - wednesday
// 4 - thursday
// 5 - friday
// 6 - saturday