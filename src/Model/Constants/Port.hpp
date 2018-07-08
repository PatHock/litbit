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
const uint8_t ACCEL_INT_1 = 10;     // uP pin 30, Arduino/ItsyBitsy pin D10
const uint8_t ACCEL_INT_2 = 9;      // uP pin 29, Arduino/ItsyBitsy pin D9

/** 
 * Bluetooth
 */
const uint8_t BLE_ACTIVE = 11;      // uP pin 12, Arduino/ItsyBitsy pin D11
const uint8_t BLE_REQN = 7;         // uP pin 1, Arduino/ItsyBitsy pin D7
const uint8_t BLE_RDYN = 0;         // uP pin 20, Arduino/ItsyBitsy pin D0
//FIXME: verify that constant below is correct
const uint8_t BLE_RST = RXLED0;     // uP pin 8, Arduino/ItsyBitsy pin "RXLED"

// EEPROM (NONE)

/** 
 * RTC
 */
const uint8_t RTC_MFP = 1;          // uP pin 21, Arduino/ItsyBitsy pin D1


#endif // PORT_HPP