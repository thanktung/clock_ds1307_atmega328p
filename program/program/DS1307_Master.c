#include "DS1307_Master.h"

// Initialize the DS1307 RTC
void RTC_Init(void) {
	I2C_Init();  // Initialize I2C communication
}

// Set time (hour, minute, second) and format (12/24-hour)
void RTC_Set_Clock(uint8_t hour, uint8_t minute, uint8_t second, uint8_t format) {
	I2C_Start(DS1307_WRITE_ADDRESS);  // Start I2C communication with DS1307
	I2C_Write(0x00);  // Point to the seconds register
	I2C_Write(decimal_to_bcd(second));  // Write seconds in BCD format
	I2C_Write(decimal_to_bcd(minute));  // Write minutes in BCD format
	I2C_Write(decimal_to_bcd(hour) | format);  // Write hours in BCD format with format flag
	I2C_Stop();  // Stop I2C communication
}

// Set date (day, date, month, year)
void RTC_Set_Calendar(uint8_t day, uint8_t date, uint8_t month, uint8_t year) {
	I2C_Start(DS1307_WRITE_ADDRESS);  // Start I2C communication with DS1307
	I2C_Write(0x03);  // Point to the day register
	I2C_Write(decimal_to_bcd(day));  // Write day in BCD format
	I2C_Write(decimal_to_bcd(date));  // Write date in BCD format
	I2C_Write(decimal_to_bcd(month));  // Write month in BCD format
	I2C_Write(decimal_to_bcd(year));  // Write year in BCD format
	I2C_Stop();  // Stop I2C communication
}

// Get individual time values
uint8_t RTC_Get_Second(void) {
	I2C_Start(DS1307_WRITE_ADDRESS);
	I2C_Write(0x00);  // Point to the seconds register
	I2C_Repeated_Start(DS1307_READ_ADDRESS);
	uint8_t second = I2C_Read_Nack();  // Read seconds and send NACK
	I2C_Stop();
	return bcd_to_decimal(second & 0x7F);  // Convert from BCD to decimal
}

uint8_t RTC_Get_Minute(void) {
	I2C_Start(DS1307_WRITE_ADDRESS);
	I2C_Write(0x01);  // Point to the minutes register
	I2C_Repeated_Start(DS1307_READ_ADDRESS);
	uint8_t minute = I2C_Read_Nack();  // Read minutes and send NACK
	I2C_Stop();
	return bcd_to_decimal(minute);  // Convert from BCD to decimal
}

uint8_t RTC_Get_Hour(void) {
	I2C_Start(DS1307_WRITE_ADDRESS);
	I2C_Write(0x02);  // Point to the hours register
	I2C_Repeated_Start(DS1307_READ_ADDRESS);
	uint8_t hour = I2C_Read_Nack();  // Read hours and send NACK
	I2C_Stop();
	return bcd_to_decimal(hour & 0x3F);  // Convert from BCD to decimal (24-hour format)
}

// Get individual date values
uint8_t RTC_Get_Day(void) {
	I2C_Start(DS1307_WRITE_ADDRESS);
	I2C_Write(0x03);  // Point to the day register
	I2C_Repeated_Start(DS1307_READ_ADDRESS);
	uint8_t day = I2C_Read_Nack();  // Read day and send NACK
	I2C_Stop();
	return bcd_to_decimal(day);  // Convert from BCD to decimal
}

uint8_t RTC_Get_Date(void) {
	I2C_Start(DS1307_WRITE_ADDRESS);
	I2C_Write(0x04);  // Point to the date register
	I2C_Repeated_Start(DS1307_READ_ADDRESS);
	uint8_t date = I2C_Read_Nack();  // Read date and send NACK
	I2C_Stop();
	return bcd_to_decimal(date);  // Convert from BCD to decimal
}

uint8_t RTC_Get_Month(void) {
	I2C_Start(DS1307_WRITE_ADDRESS);
	I2C_Write(0x05);  // Point to the month register
	I2C_Repeated_Start(DS1307_READ_ADDRESS);
	uint8_t month = I2C_Read_Nack();  // Read month and send NACK
	I2C_Stop();
	return bcd_to_decimal(month);  // Convert from BCD to decimal
}

uint8_t RTC_Get_Year(void) {
	I2C_Start(DS1307_WRITE_ADDRESS);
	I2C_Write(0x06);  // Point to the year register
	I2C_Repeated_Start(DS1307_READ_ADDRESS);
	uint8_t year = I2C_Read_Nack();  // Read year and send NACK
	I2C_Stop();
	return bcd_to_decimal(year);  // Convert from BCD to decimal
}

// Utility functions
uint8_t bcd_to_decimal(uint8_t bcd) {
	return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

uint8_t decimal_to_bcd(uint8_t decimal) {
	return ((decimal / 10) << 4) | (decimal % 10);
}
