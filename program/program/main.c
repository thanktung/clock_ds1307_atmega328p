#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "DS1307_Master.h"
#include "Led7Segment.h"
#include "I2C_Master.h"

void button_init();
int check_button0();
int check_button1();
int check_setup_state();

uint8_t display_mode = 0;
uint8_t setup = 0;
int setup_step = -1;

uint8_t time_data[7] = {0};
uint8_t time_setup[7] = {0};
uint8_t setup_initialized = 0; // Flag to ensure setup values are copied only once

int main(void) {
	Led7Segment_Init();
	RTC_Init();
	button_init();

	while (1) {
		// Check if both buttons are pressed to enter setup mode
		if (check_setup_state()) {
			setup = 1; // Enter setup mode
		}

		switch (setup) {
			case 0: // Normal mode: Display time or date
			if (check_button0()) {
				_delay_ms(20);
				display_mode = !display_mode; // Switch to time display mode
			}



			// Retrieve current time and date from RTC
			time_data[0] = RTC_Get_Hour();
			time_data[1] = RTC_Get_Minute();
			time_data[2] = RTC_Get_Second();
			time_data[3] = RTC_Get_Date();
			time_data[4] = RTC_Get_Month();
			time_data[5] = RTC_Get_Year();
			time_data[6] = RTC_Get_Day();

			if (display_mode == 0) {
				display_time(time_data[0], time_data[1], time_data[2]); // Display time
				} else {
				display_date(time_data[3], time_data[4], time_data[5], time_data[6]); // Display date
			}
			break;

			case 1: // Setup mode: Adjust time and date
			// Copy current time and date into setup array only once
			if (!setup_initialized) {
				for (int i = 0; i < 7; i++) {
					time_setup[i] = time_data[i];
				}
				setup_initialized = 1; // Ensure this happens only once
			}

			// Move to the next setup step
			if (check_button1()) {
				_delay_ms(20);
				setup_step++;
			}

			// Increment the value for the current setup step
			if (check_button0()) {
				switch (setup_step) {
					case 0: // Hour
					time_setup[0]++;
					if (time_setup[0] > 23) time_setup[0] = 0; // Limit to 0-23
					break;
					case 1: // Minute
					time_setup[1]++;
					if (time_setup[1] > 59) time_setup[1] = 0; // Limit to 0-59
					break;
					case 2: // Second
					time_setup[2]++;
					if (time_setup[2] > 59) time_setup[2] = 0; // Limit to 0-59
					break;
					case 3: // Day
					time_setup[3]++;
					if (time_setup[3] > 31) time_setup[3] = 1; // Limit to 1-31 (basic check, no month-specific validation)
					break;
					case 4: // Month
					time_setup[4]++;
					if (time_setup[4] > 12) time_setup[4] = 1; // Limit to 1-12
					break;
					case 5: // Year
					time_setup[5]++;
					if (time_setup[5] > 99) time_setup[5] = 0; // Limit to 0-99
					break;
					case 6: // Day of the week
					time_setup[6]++;
					if (time_setup[6] > 7) time_setup[6] = 1; // Limit to 1-7
					break;
				}
			}

			// Exit setup mode and send new time to RTC
			if (setup_step > 6) {
				setup = 0; // Exit setup mode
				setup_step = -1;
				setup_initialized = 0; // Reset flag for the next setup
				// Update RTC with new time and date
				RTC_Set_Clock(time_setup[0], time_setup[1], time_setup[2], HOUR_FORMAT_24);
				RTC_Set_Calendar(time_setup[6], time_setup[3], time_setup[4], time_setup[5]);
			}

			// Display the setup values
			switch (setup_step) {
				case 0:
				display_hour(time_setup[0]); // Display hour during setup
				break;
				case 1:
				display_minute(time_setup[1]); // Display minute during setup
				break;
				case 2:
				display_second(time_setup[2]); // Display second during setup
				break;
				case 3:
				display_day(time_setup[3]); // Display day during setup
				break;
				case 4:
				display_month(time_setup[4]); // Display month during setup
				break;
				case 5:
				display_year(time_setup[5]); // Display year during setup
				break;
				case 6:
				display_dayofweek(time_setup[6]); // Display day of the week during setup
				break;
				default:
				// Optional: Handle invalid step case
				break;
			}
			
			break;
		}
	}
}

void button_init() {
	DDRB &= (~(1 << PINB0)) & (~(1 << PINB1)); // Set PB0 and PB1 as input
	PORTB |= (1 << PINB0) | (1 << PINB1); // Enable pull-up resistors on PB0 and PB1
}

int check_button0() {
	static uint8_t prev_state = 1;
	uint8_t current_state = PINB & (1 << PINB0);

	if (!current_state && prev_state) { // Detect falling edge
		prev_state = current_state;
		return 1;
	}

	prev_state = current_state;
	return 0;
}

int check_button1() {
	static uint8_t prev_state = 1;
	uint8_t current_state = PINB & (1 << PINB1);

	if (!current_state && prev_state) { // Detect falling edge
		prev_state = current_state;
		return 1;
	}

	prev_state = current_state;
	return 0;
}

int check_setup_state() {
	// Check if both PB0 and PB1 are pressed simultaneously
	uint8_t current_state_0 = PINB & (1 << PINB0);
	uint8_t current_state_1 = PINB & (1 << PINB1);

	// Return 1 if both buttons are pressed (falling edge)
	if (!current_state_0 && !current_state_1) {
		return 1;
	}
	return 0;
}