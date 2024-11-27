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
int check_alarm_state();

uint8_t display_mode = 0;
uint8_t setup = 0;
int setup_step = -1;

uint8_t alarm = 0;
uint8_t alarm_value[3] = {0};
uint8_t alarm_step = 0;
uint8_t alarm_flag = 0;

uint8_t time_data[7] = {0};
uint8_t time_setup[7] = {0};
uint8_t setup_initialized = 0;

void reset_setup() {
	setup_step = -1;
	setup_initialized = 0;
}

void reset_alarm() {
	alarm_step = 0;
	alarm_flag = 0;
}

int main(void) {
	Led7Segment_Init();
	RTC_Init();
	button_init();

	while (1) {
		// Chuy?n tr?ng thái setup ho?c alarm mode
		if (check_setup_state()) {
			setup = 1;  // Vào ch? ?? setup
			reset_setup();
		}

		if (check_alarm_state()) {
			setup = 2;  // Vào ch? ?? báo th?c
			reset_alarm();
		}

		switch (setup) {
			case 0:  // Ch? ?? bình th??ng
			if (check_button0()) {
				_delay_ms(20);
				display_mode = 0;  // Hi?n th? th?i gian
			}
			if (check_button1()) {
				_delay_ms(20);
				display_mode = 1;  // Hi?n th? ngày tháng
			}

			// L?y d? li?u th?i gian t? RTC
			time_data[0] = RTC_Get_Hour();
			time_data[1] = RTC_Get_Minute();
			time_data[2] = RTC_Get_Second();
			time_data[3] = RTC_Get_Date();
			time_data[4] = RTC_Get_Month();
			time_data[5] = RTC_Get_Year();
			time_data[6] = RTC_Get_Day();

			if (display_mode == 0) {
				display_time(time_data[0], time_data[1], time_data[2]);
				} else {
				display_date(time_data[3], time_data[4], time_data[5], time_data[6]);
			}


			break;

			case 1:  // Ch? ?? setup
			if (!setup_initialized) {
				for (int i = 0; i < 7; i++) {
					time_setup[i] = time_data[i];
				}
				setup_initialized = 1;
			}

			if (check_button1()) {
				_delay_ms(20);
				setup_step++;
				if (setup_step > 6) {
					setup = 0;  // Thoát ch? ?? setup
					reset_setup();
					// C?p nh?t RTC
					RTC_Set_Clock(time_setup[0], time_setup[1], time_setup[2], HOUR_FORMAT_24);
					RTC_Set_Calendar(time_setup[6], time_setup[3], time_setup[4], time_setup[5]);
				}
			}

			if (check_button0()) {
				switch (setup_step) {
					case 0: time_setup[0] = (time_setup[0] + 1) % 24; break;  // Gi?i h?n gi? 0-23
					case 1: time_setup[1] = (time_setup[1] + 1) % 60; break;  // Gi?i h?n phút 0-59
					case 2: time_setup[2] = (time_setup[2] + 1) % 60; break;  // Gi?i h?n giây 0-59
					case 3: time_setup[3] = (time_setup[3] % 31) + 1; break;  // Gi?i h?n ngày 1-31
					case 4: time_setup[4] = (time_setup[4] % 12) + 1; break;  // Gi?i h?n tháng 1-12
					case 5: time_setup[5] = (time_setup[5] + 1) % 100; break;  // Gi?i h?n n?m 0-99
					case 6: time_setup[6] = (time_setup[6] % 7) + 1; break;  // Gi?i h?n th? 1-7
				}
			}

			// Hi?n th? giá tr? setup
			switch (setup_step) {
				case 0: display_hour(time_setup[0]); break;
				case 1: display_minute(time_setup[1]); break;
				case 2: display_second(time_setup[2]); break;
				case 3: display_day(time_setup[3]); break;
				case 4: display_month(time_setup[4]); break;
				case 5: display_year(time_setup[5]); break;
				case 6: display_dayofweek(time_setup[6]); break;
			}
			break;

			case 2:  // Ch? ?? báo th?c
			if (check_button1()) {
				_delay_ms(20);
				alarm_step = (alarm_step + 1) % 2;
			}

			if (check_button0()) {
				switch (alarm_step) {
					case 0: alarm_value[0] = (alarm_value[0] + 1) % 24; break;  // Gi?i h?n gi? 0-23
					case 1: alarm_value[1] = (alarm_value[1] + 1) % 60; break;  // Gi?i h?n phút 0-59
				}
			}

			if (alarm_value[0] == RTC_Get_Hour() &&
			alarm_value[1] == RTC_Get_Minute() ) {
				alarm_flag = 1;  // Kích ho?t báo th?c
			}

			display_alarm(alarm_value[0], alarm_value[1]);
			
			
			if (alarm_flag){
				for (int i = 0; i< 8; i++){
					display_digit(i, 8);
					_delay_ms(100);
				}
			}
			
			
			break;
		}
	}
}

void button_init() {
	DDRB &= ~((1 << PINB0) | (1 << PINB1));  // ??t PB0 và PB1 làm input
	PORTB |= (1 << PINB0) | (1 << PINB1);    // Kích ho?t ?i?n tr? pull-up
}

int check_button0() {
	static uint8_t prev_state = 1;
	uint8_t current_state = PINB & (1 << PINB0);

	if (!current_state && prev_state) {
		prev_state = current_state;
		return 1;
	}
	prev_state = current_state;
	return 0;
}

int check_button1() {
	static uint8_t prev_state = 1;
	uint8_t current_state = PINB & (1 << PINB1);

	if (!current_state && prev_state) {
		prev_state = current_state;
		return 1;
	}
	prev_state = current_state;
	return 0;
}

int check_setup_state() {
	return (!(PINB & (1 << PINB0)) && check_button1());  // gi? nút B0 và B1
}

int check_alarm_state() {
	return (!(PINB & (1 << PINB1)) && check_button0());  // gi? nút B1 và nút B0
}
