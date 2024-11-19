#ifndef LED7SEGMENT_H
#define LED7SEGMENT_H

#include <avr/io.h>
#include <util/delay.h>

// 7-segment codes for digits 0-9
extern uint8_t segment_codes[];

// Function to initialize the I/O pins for 7-segment display
void Led7Segment_Init(void);

// Function to display a single digit on the 7-segment display
void display_digit(uint8_t digit, uint8_t value);

void display_test();

void display_time(uint8_t hour, uint8_t minute, uint8_t second);
void display_date(uint8_t date, uint8_t month, uint8_t year);

#endif // LED7SEGMENT_H
