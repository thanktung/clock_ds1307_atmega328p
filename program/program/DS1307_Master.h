#ifndef DS1307_MASTER_H_
#define DS1307_MASTER_H_

#include <avr/io.h>
#include "I2C_Master.h"  // Include I2C library for communication

// DS1307 I2C device addresses
#define DS1307_WRITE_ADDRESS  0xD0   // DS1307 I2C address for write operations
#define DS1307_READ_ADDRESS   0xD1   // DS1307 I2C address for read operations

// Hour format flags
#define HOUR_FORMAT_12_AM     0x40   // 12-hour format, AM
#define HOUR_FORMAT_12_PM     0x60   // 12-hour format, PM
#define HOUR_FORMAT_24        0x00   // 24-hour format

// Function declarations for RTC DS1307
void RTC_Init(void);
void RTC_Set_Clock(uint8_t hour, uint8_t minute, uint8_t second, uint8_t format);
void RTC_Set_Calendar(uint8_t day, uint8_t date, uint8_t month, uint8_t year);

uint8_t RTC_Get_Second(void);
uint8_t RTC_Get_Minute(void);
uint8_t RTC_Get_Hour(void);
uint8_t RTC_Get_Day(void);
uint8_t RTC_Get_Date(void);
uint8_t RTC_Get_Month(void);
uint8_t RTC_Get_Year(void);

// Utility function for conversions
uint8_t bcd_to_decimal(uint8_t bcd);
uint8_t decimal_to_bcd(uint8_t decimal);

#endif /* DS1307_MASTER_H_ */
