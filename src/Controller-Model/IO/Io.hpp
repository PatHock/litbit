/**
 * Io.hpp
 * Allows for PCINT pins to be used as normal interrupt pins
 * https://playground.arduino.cc/Main/PcInt
 * 
 * Patrick Hock
 * August 6, 2018
 */

#include "pins_arduino.h"
#include "Arduino.h"
#include <avr/io.h>
#include <stdint.h>            // has to be added to use uint8_t
#include <avr/interrupt.h>    // Needed to use interrupts



