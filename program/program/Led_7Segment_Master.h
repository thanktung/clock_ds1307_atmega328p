/*
 * Led_7Segment_Master.h
 *
 * Created: 11/19/2024 7:52:58 AM
 *  Author: Vuong Thanh Tung
 */ 


#ifndef LED_7SEGMENT_MASTER_H_
#define LED_7SEGMENT_MASTER_H_

#ifndef F_CPU
#define F_CPU 1e6
#endif

#include <avr/io.h>
#include <util/delay.h>

// Segment codes for 0-9 (each byte represents the segments a-g for a digit)
uint8_t segment_codes[] = {
	0x3F, // 0  => abcdefg
	0x06, // 1  =>  bc
	0x5B, // 2  => abdeg
	0x4F, // 3  => abcdg
	0x66, // 4  => bcdg
	0x6D, // 5  => acdfg
	0x7D, // 6  => acdefg
	0x07, // 7  => abc
	0x7F, // 8  => abcdefg
	0x6F  // 9  => abcdfg
};

// Initialize I/O ports (PORTB, PORTC, PORTD as outputs)
void init_io() {
	DDRB = 0xFF;  // Set PORTB as output (for controlling digits 1-4)
	DDRC = 0xFF;  // Set PORTC as output (for controlling digits 5-8)
	DDRD = 0xFF;  // Set PORTD as output (for controlling segments a-g)
}

// Display one digit with the given value on the specified digit
void display_digit(uint8_t digit, uint8_t value) {
	PORTB = 0x00; // Turn off all PORTB pins (to deactivate digits 1-4)
	PORTC = 0x00; // Turn off all PORTC pins (to deactivate digits 5-8)

	// Activate the correct digit (digit1 to digit4 on PORTB, digit5 to digit8 on PORTC)
	if (digit < 4) {
		PORTB |= (1 << (PB2 + digit)); // Activate digits 1-4 (PB2 to PB5)
		} else {
		PORTC |= (1 << (PC0 + (digit - 4))); // Activate digits 5-8 (PC0 to PC3)
	}

	// Display the corresponding segment pattern for the number
	PORTD = segment_codes[value];

	_delay_ms(5);  // Small delay to make the digit clearly visible
}




#endif /* LED_7SEGMENT_MASTER_H_ */