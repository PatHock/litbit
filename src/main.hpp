#ifndef MAIN_HPP
#define MAIN_HPP

#include <stdint.h>
#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>


// /**
//  * Setup and Initialization functions
//  */

// /**
// * Function implements any configuration necessary to operate
// * on the SPI bus
// */
// void setupSPI(){}

// /**
// * Function implements any configuration necessary to operate
// * on the i2c bus
// */
// void setupI2C(){}

// /*
// * Conduct any initialization necessary of the ADXL345
// * either internally to Arduino or external in the peripheral
// */
// void setupADXL345(){}

// /**
// * Conduct any initialization necessary of the RTC
// * either internally to Arduino or external in the peripheral
// * Initialize the current date/time in MM/DD/YY HH:MM:SS format
// */
// void setupRTC(DateTime* init){}

// /**
// * Conduct any initialization necessary of the EERPOM
// * either internally to Arduino or external in the peripheral
// */
// void setupEEPROM(){}

// /**
//  * Data read/write functions
//  */

// /**
//  * Function takes a pointer to an Accel data object
//  * and populates the contents with the X, Y, and Z acceleration values.
//  * Value may be raw readings or normalized relative to 0g.
//  */
// void readAcceleration(Accel* data){}

// /**
//  * Function takes a pointer to a DateTime object and
//  * populates with the current DateTime in MM/DD/YYYY HH:MM:SS
//  * format. Return values must be human readable
//  */
// void readDateTime(DateTime* data){}

// /**
//  * Function writes a series of uint16_t values to the EEPROM
//  * from the data array. Length of array is specified by the len parameter.
//  * All writing is assumed to occur at EEPROM storage address 0x0.
//  * Any existing data should be overwritten.
//  */
// void writeDataToEEPROM(uint16_t* data, uint16_t len){}

// /**
//  * Function reads a sequence of uint16_t values from the EEPROM
//  * and stores the result in the buffer array. Length of buffer is
//  * specified by the len parameter. All reads are assumed to begin at EEPROM storage
//  * address 0x0.
//  */
// void readDataFromEEPROM(uint16_t* buffer, uint16_t len){}

#endif  // MAIN_HPP