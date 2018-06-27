/**
 * Display.hpp
 * Sparkfun Micro OLED Breakout (Qwiic)
 * 
 * Patrick Hock 
 * June 26, 2018
 */

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Arduino.h>
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library
#include <Wire.h>

#define DISPLAY_DC 1
#define DISPLAY_RST 9

class Display
{
    public:
        Display(void);     // Constructor
        ~Display(void); // Destructor
    
    private:
        // MicroOLED oled;

};

#endif  // DISPLAY_HPP