#ifndef F_CPU
#define F_CPU 16000000UL  
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "DS1307_Master.h"  
#include "Led7Segment.h"    
#include "I2C_Master.h"     

void button_init();
int check_button();

int main(void) {
	
	Led7Segment_Init();  
	RTC_Init();          
	button_init();       

	uint8_t display_mode = 0; // 0: Show time, 1: Show date

	while (1) {
		
		if (check_button0()) {
			_delay_ms(20);  
			display_mode = 0;  
		}
		
		if (check_button1()){
			_delay_ms(20);
			display_mode = 1;
		}

		if (display_mode == 0) {
			uint8_t second = RTC_Get_Second();
			uint8_t minute = RTC_Get_Minute();
			uint8_t hour = RTC_Get_Hour();
			display_time(hour, minute, second);  // Display time
			} else {
			uint8_t date = RTC_Get_Date();
			uint8_t month = RTC_Get_Month();
			uint8_t year = RTC_Get_Year();
			display_date(date, month, year);  // Display date
		}
	}
}


void button_init() {
	DDRB &= (~(1 << PINB0)) & (~(1 << PINB1));  
	PORTB |= (1 << PINB0) | (1 << PINB1);  
}

int check_button0() {
	static uint8_t prev_state = 1;  // Previous PB0 state
	uint8_t current_state = PINB & (1 << PINB0);  // Read current PB0 state

	if (!current_state && prev_state) {  // Detect button press (falling edge)
		prev_state = current_state;  // Update previous state
		return 1;  // Button press detected
	}

	prev_state = current_state;  // Update previous state
	return 0;  // No button press
}

int check_button1() {
	static uint8_t prev_state = 1;  // Previous PB0 state
	uint8_t current_state = PINB & (1 << PINB1);  // Read current PB0 state

	if (!current_state && prev_state) {  // Detect button press (falling edge)
		prev_state = current_state;  // Update previous state
		return 1;  // Button press detected
	}

	prev_state = current_state;  // Update previous state
	return 0;  // No button press
}
