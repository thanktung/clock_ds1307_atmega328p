#define F_CPU 1000000UL
#include "I2C_Master.h"

// Function to initialize the I2C peripheral
void I2C_Init() {
	TWSR = 0x00; // Set the prescaler to 1 (no prescaling)
	TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2; // Set the I2C clock speed based on F_CPU and SCL_CLOCK
	TWCR = (1 << TWEN); // Enable the TWI (I2C) peripheral
}

// Function to send a start condition and address to initiate communication with a slave device
void I2C_Start(uint8_t address) {
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); // Send start condition
	while (!(TWCR & (1 << TWINT))); // Wait for the start condition to be transmitted
	TWDR = address; // Load the address into the data register
	TWCR = (1 << TWEN) | (1 << TWINT); // Send the address to the slave
	while (!(TWCR & (1 << TWINT))); // Wait for the transmission to complete
}

// Function to send a stop condition to end the I2C communication
void I2C_Stop() {
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT); // Send stop condition
	while (TWCR & (1 << TWSTO)); // Wait until stop condition is transmitted
}

// Function to write a byte of data to the I2C bus
void I2C_Write(uint8_t data) {
	TWDR = data; // Load data to be transmitted into the data register
	TWCR = (1 << TWEN) | (1 << TWINT); // Initiate the transmission of the data
	while (!(TWCR & (1 << TWINT))); // Wait for the transmission to complete
}

// Function to read a byte of data from the I2C bus and send an ACK to continue reading
uint8_t I2C_Read_Ack() {
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); // Enable ACK for the next byte
	while (!(TWCR & (1 << TWINT))); // Wait for the data to be received
	return TWDR; // Return the received data
}

// Function to read a byte of data from the I2C bus and send a NACK to end the reading
uint8_t I2C_Read_Nack() {
	TWCR = (1 << TWEN) | (1 << TWINT); // No ACK, just read the byte
	while (!(TWCR & (1 << TWINT))); // Wait for the data to be received
	return TWDR; // Return the received data
}

// Function to send a repeated start condition and address to re-initiate communication
void I2C_Repeated_Start(uint8_t address) {
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); // Send start condition
	while (!(TWCR & (1 << TWINT))); // Wait for the start condition to be transmitted
	TWDR = address; // Load the address into the data register
	TWCR = (1 << TWEN) | (1 << TWINT); // Send the address to the slave
	while (!(TWCR & (1 << TWINT))); // Wait for the transmission to complete
}
