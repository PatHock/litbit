/**
 * Port.hpp
 * Contains definitions for each I/O pin
 * 
 * Patrick Hock 
 * July 08, 2018
 */

#ifndef PORT_HPP
#define PORT_HPP

#include <stdint.h>
#include <Arduino.h>    // Needed for RXLED0 Value

/** 
 * Accelerometer
 */
const uint8_t PIN_ACCEL_INT_1 = 10;     // uP pin 30, Arduino/ItsyBitsy pin D10
const uint8_t PIN_ACCEL_INT_2 = 9;      // uP pin 29, Arduino/ItsyBitsy pin D9

/** 
 * Bluetooth
 */
const uint8_t PIN_BLE_ACTIVE = 11;      // uP pin 12, Arduino/ItsyBitsy pin D11
const uint8_t PIN_BLE_REQN = 7;         // uP pin 1, Arduino/ItsyBitsy pin D7
const uint8_t PIN_BLE_RDYN = 0;         // uP pin 20, Arduino/ItsyBitsy pin D0
//FIXME: commented code should work for PCB, below is for breadboard...
const uint8_t PIN_BLE_RST = 5;
// const uint8_t PIN_BLE_RST = RXLED0;     // uP pin 8, Arduino/ItsyBitsy pin "RXLED"

// EEPROM (NONE)

/** 
 * RTC
 */
const uint8_t PIN_RTC_MFP = 1;          // uP pin 21, Arduino/ItsyBitsy pin D1

/**
 * Display
 * The Following pins are NC
 */
const uint8_t PIN_DISPLAY_DC = 1;
const uint8_t PIN_DISPLAY_RST = 13;

#endif // PORT_HPP