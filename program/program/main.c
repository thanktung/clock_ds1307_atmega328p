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
volatile uint8_t display_mode = 0; // 0: Show time, 1: Show date

// M?ng ?? l?u tr? gi?, ph�t, gi�y, ng�y, th�ng, n?m, th?
uint8_t time_data[7] = {0}; // {hour, minute, second, date, month, year, day_of_week}

int main(void) {
	Led7Segment_Init();
	RTC_Init();
	button_init();

	while (1) {
		// Ki?m tra n�t b?m ?? chuy?n ??i gi?a ch? ?? hi?n th? th?i gian v� ng�y th�ng
		if (check_button0()) {
			_delay_ms(20);
			display_mode = 0; // Ch? ?? hi?n th? gi?
		}
		
		if (check_button1()) {
			_delay_ms(20);
			display_mode = 1; // Ch? ?? hi?n th? ng�y th�ng
		}

		// L?y th�ng tin t? RTC v� l?u v�o m?ng
		time_data[0] = RTC_Get_Hour();  // L?y gi?
		time_data[1] = RTC_Get_Minute(); // L?y ph�t
		time_data[2] = RTC_Get_Second(); // L?y gi�y
		time_data[3] = RTC_Get_Date();   // L?y ng�y
		time_data[4] = RTC_Get_Month();  // L?y th�ng
		time_data[5] = RTC_Get_Year();   // L?y n?m
		time_data[6] = RTC_Get_Day(); // L?y th?

		// Hi?n th? gi? ho?c ng�y th�ng t�y thu?c v�o display_mode
		if (display_mode == 0) {
			// Hi?n th? gi?, ph�t, gi�y
			display_time(time_data[0], time_data[1], time_data[2]);
			} else {
			// Hi?n th? ng�y, th�ng, n?m
			display_date(time_data[3], time_data[4], time_data[5]);
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
	static uint8_t prev_state = 1;  // Previous PB1 state
	uint8_t current_state = PINB & (1 << PINB1);  // Read current PB1 state

	if (!current_state && prev_state) {  // Detect button press (falling edge)
		prev_state = current_state;  // Update previous state
		return 1;  // Button press detected
	}

	prev_state = current_state;  // Update previous state
	return 0;  // No button press
}
