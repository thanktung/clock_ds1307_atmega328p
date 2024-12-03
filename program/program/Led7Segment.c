#include "Led7Segment.h"

// 7-segment codes for digits 0-9
uint8_t segment_codes[] = {
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

// Function to initialize the I/O pins for the 7-segment display
void Led7Segment_Init(void) {
	DDRB |= (1 << PINB2) | (1 << PINB3) | (1 << PINB4) | (1 << PINB5); // Set PORTB as output (for controlling digits 1-4)
	DDRC |= (1 << PINC0) | (1 << PINC1) | (1 << PINC2) | (1 << PINC3); // Set PORTC as output (for controlling digits 5-8)
	DDRD = 0xFF; // Set PORTD as output (for controlling segments a-g)
}

// Function to display a single digit on the 7-segment display
void display_digit(uint8_t digit, uint8_t value) {
	// Activate the correct digit (digit1 to digit4 on PORTB, digit5 to digit8 on PORTC)
	PORTB &= (~(1 << PINB2)) & (~(1 << PINB3)) & (~(1 << PINB4)) & (~(1 << PINB5));
	PORTC &= (~(1 << PINC0)) & (~(1 << PINC1)) & (~(1 << PINC2)) & (~(1 << PINC3));
	if (digit < 4) {
		PORTB |= (1 << (PINB2 + digit)); // Activate digits 1-4 (PB2 to PB5)
		} else {
		PORTC |= (1 << (PINC0 + (digit - 4))); // Activate digits 5-8 (PC0 to PC3)
	}

	// Display the corresponding segment pattern for the number
	PORTD = segment_codes[value];
	if (digit == 1 || digit == 3 || digit == 5 || digit == 7){
		PORTD |= (1 << PIND7);
	} else PORTD &= (~(1 << PIND7));
	//_delay_ms(5);  // Small delay to make the digit clearly visible
	
}

// Function to run a test pattern on all digits
void display_test(){
	for (int i = 0; i < 8; i++) {
		display_digit(i, 5);  // Display the number 5 on each digit
		_delay_ms(500);  // Delay for half a second
	}
}

// Function to display time in HH:MM:SS format on the 7-segment display
void display_time(uint8_t hour, uint8_t minute, uint8_t second) {
	// Split hours, minutes, and seconds into tens and ones digits
	uint8_t hour_tens = hour / 10;      // Tens place of hour
	uint8_t hour_ones = hour % 10;      // Ones place of hour
	uint8_t minute_tens = minute / 10;  // Tens place of minute
	uint8_t minute_ones = minute % 10;  // Ones place of minute
	uint8_t second_tens = second / 10;  // Tens place of second
	uint8_t second_ones = second % 10;  // Ones place of second

	// Display the time on the 7-segment display (LED1 to LED6)
	display_digit(0, hour_tens);   // LED1: Tens place of hour
	_delay_ms(40);
	display_digit(1, hour_ones);   // LED2: Ones place of hour
	_delay_ms(40);
	display_digit(2, minute_tens); // LED3: Tens place of minute
	_delay_ms(40);
	display_digit(3, minute_ones); // LED4: Ones place of minute
	_delay_ms(40);
	display_digit(4, second_tens); // LED5: Tens place of second
	_delay_ms(40);
	display_digit(5, second_ones); // LED6: Ones place of second
	_delay_ms(40);
}

// Function to display the date in DD/MM/YYYY format on the 7-segment display
void display_date(uint8_t date, uint8_t month, uint8_t year, uint8_t day_of_week) {
	// Split the date, month, and year into tens and ones digits
	uint8_t date_tens = date / 10;      // Tens place of date
	uint8_t date_ones = date % 10;      // Ones place of date
	uint8_t month_tens = month / 10;    // Tens place of month
	uint8_t month_ones = month % 10;    // Ones place of month
	uint8_t year_tens = year / 10;      // Tens place of year
	uint8_t year_ones = year % 10;      // Ones place of year


	// Display the date, month, and year on the 7-segment display (LED1 to LED6)
	display_digit(0, date_tens);        // LED1: Tens place of date
	_delay_ms(40);
	display_digit(1, date_ones);        // LED2: Ones place of date
	_delay_ms(40);
	display_digit(2, month_tens);       // LED3: Tens place of month
	_delay_ms(40);
	display_digit(3, month_ones);       // LED4: Ones place of month
	_delay_ms(40);
	display_digit(4, year_tens);        // LED5: Tens place of year
	_delay_ms(40);
	display_digit(5, year_ones);        // LED6: Ones place of year
	_delay_ms(40);
	display_digit(7, day_of_week);
	_delay_ms(40);
}

void display_alarm(uint8_t hour, uint8_t minute) {
	// Split hours, minutes, and seconds into tens and ones digits
	uint8_t hour_tens = hour / 10;      // Tens place of hour
	uint8_t hour_ones = hour % 10;      // Ones place of hour
	uint8_t minute_tens = minute / 10;  // Tens place of minute
	uint8_t minute_ones = minute % 10;  // Ones place of minute

	// Display the time on the 7-segment display (LED1 to LED6)
	display_digit(0, hour_tens);   // LED1: Tens place of hour
	_delay_ms(40);
	display_digit(1, hour_ones);   // LED2: Ones place of hour
	_delay_ms(40);
	display_digit(2, minute_tens); // LED3: Tens place of minute
	_delay_ms(40);
	display_digit(3, minute_ones); // LED4: Ones place of minute
	_delay_ms(40);
}


void display_hour(uint8_t hour) {
	display_digit(0, hour / 10); // LED1 hi?n th? hàng ch?c gi?
	_delay_ms(40);
	display_digit(1, hour % 10); // LED2 hi?n th? hàng ??n v? gi?
	_delay_ms(40);
}

void display_minute(uint8_t minute) {
	display_digit(2, minute / 10); // LED3 hi?n th? hàng ch?c phút
	_delay_ms(40);
	display_digit(3, minute % 10); // LED4 hi?n th? hàng ??n v? phút
	_delay_ms(40);
}

void display_second(uint8_t second) {
	display_digit(4, second / 10); // LED5 hi?n th? hàng ch?c giây
	_delay_ms(40);
	display_digit(5, second % 10); // LED6 hi?n th? hàng ??n v? giây
	_delay_ms(40);
}

void display_day(uint8_t date) {
	display_digit(0, date / 10); // LED1 hi?n th? hàng ch?c ngày
	_delay_ms(40);
	display_digit(1, date % 10); // LED2 hi?n th? hàng ??n v? ngày
	_delay_ms(40);
}

void display_month(uint8_t month) {
	display_digit(2, month / 10); // LED3 hi?n th? hàng ch?c tháng
	_delay_ms(40);
	display_digit(3, month % 10); // LED4 hi?n th? hàng ??n v? tháng
	_delay_ms(40);
}

void display_year(uint8_t year) {
	display_digit(4, year / 10); // LED5 hi?n th? hàng ch?c n?m
	_delay_ms(40);
	display_digit(5, year % 10); // LED6 hi?n th? hàng ??n v? n?m
	_delay_ms(40);
}

void display_dayofweek(uint8_t day_of_week) {
	display_digit(7, day_of_week); // LED8 hi?n th? th? trong tu?n
	_delay_ms(40);
}
