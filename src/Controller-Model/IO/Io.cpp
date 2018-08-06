/**
 * Io.cpp
 * Allows for PCINT pins to be used as normal interrupt pins
 * https://playground.arduino.cc/Main/PcInt
 * 
 * Patrick Hock
 * August 6, 2018
 */

/*
 * Theory: all IO pins on Atmega32u4 are covered by Pin Change Interrupts.
 * The PCINT corresponding to the pin must be enabled and masked, and
 * an ISR routine provided.  Since PCINTs are per port, not per pin, the ISR
 * must use some logic to actually implement a per-pin interrupt service.
 */

#include "Io.hpp"

/* Pin to interrupt map:
 * https://www.arduino.cc/en/Hacking/PinMapping32u4
 * PCINT0: RXLED   PCINT1: SCK   PCINT2: MOSI  PCINT3: MISO
 * PCINT4-7: D8-D11
 * 
 * Note: Below are true for ATMEGA128
 * D0-D7 = PCINT 16-23 = PCIR2 = PD = PCIE2 = pcmsk2
 * D8-D13 = PCINT 0-5 = PCIR0 = PB = PCIE0 = pcmsk0
 * A0-A5 (D14-D19) = PCINT 8-13 = PCIR1 = PC = PCIE1 = pcmsk1
 */




/** 
 * Accelerometer
 */
// const uint8_t PIN_ACCEL_INT_1 = 10;     // uP pin 30, Arduino/ItsyBitsy pin D10
// const uint8_t PIN_ACCEL_INT_2 = 9;      // uP pin 29, Arduino/ItsyBitsy pin D9

