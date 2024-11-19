#ifndef I2C_MASTER_H_
#define I2C_MASTER_H_

#include <avr/io.h>

// Define the clock speed for the I2C bus (100 kHz by default)
#define SCL_CLOCK 100000UL

// Function prototypes for I2C operations

// Initializes the I2C (TWI) module with the appropriate clock settings
void I2C_Init();

// Starts communication with a given I2C address
void I2C_Start(uint8_t address);

// Stops communication with the I2C device
void I2C_Stop();

// Writes a byte of data to the I2C bus
void I2C_Write(uint8_t data);

// Reads a byte of data from the I2C bus and sends an ACK for further reads
uint8_t I2C_Read_Ack();

// Reads a byte of data from the I2C bus and sends a NACK to indicate the end of transmission
uint8_t I2C_Read_Nack();

// Sends a repeated start condition to re-initiate communication with the given address
void I2C_Repeated_Start(uint8_t address);

#endif /* I2C_MASTER_H_ */
