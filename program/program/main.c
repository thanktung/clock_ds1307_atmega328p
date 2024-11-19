#ifndef F_CPU
#define F_CPU 1000000UL  // Define CPU frequency for delay functions
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "DS1307_Master.h"  // Include DS1307 RTC library
#include "Led7Segment.h"    // Include 7-segment display library
#include "I2C_Master.h"     // Include I2C master communication library

int main(void) {
	// Initialize system components
	Led7Segment_Init();  // Initialize 7-segment display
	RTC_Init();          // Initialize RTC (DS1307)

	// Set initial time and date on DS1307
	RTC_Set_Clock(23, 59, 50, HOUR_FORMAT_24);  // Set time to 12:59:40 (24-hour format)
	RTC_Set_Calendar(7, 31, 12, 22);            // Set date to 31/12/2022 (7th day of the week)

	while (1) {
		// Read time from DS1307 RTC
		uint8_t second = RTC_Get_Second();  // Get seconds
		uint8_t minute = RTC_Get_Minute();  // Get minutes
		uint8_t hour = RTC_Get_Hour();      // Get hours
		
		display_time(hour, minute, second);
		
		// Read date from DS1307 RTC
		uint8_t day = RTC_Get_Day();        // Get day of the week
		uint8_t date = RTC_Get_Date();      // Get date (DD)
		uint8_t month = RTC_Get_Month();    // Get month (MM)
		uint8_t year = RTC_Get_Year();      // Get year (YY)

		// Display date (DD/MM/YY) on the 7-segment display
		//display_date(date, month, year);    // Call the function to display date
		_delay_ms(10);  // Delay to update display every 100ms
	}
}
