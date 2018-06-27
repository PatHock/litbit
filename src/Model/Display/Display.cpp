/**
 * Display.cpp
 * Sparkfun Micro OLED Breakout (Qwiic)
 * 
 * Patrick Hock 
 * June 26, 2018
 */

#include "Display.hpp"

/**
 * Constructor
 */
Display::Display(void) 
{
    MicroOLED oled(DISPLAY_RST, DISPLAY_DC);    // Initialize the OLED
    oled.begin();    // Initialize the OLED
    oled.clear(ALL); // Clear the display's internal memory
    oled.display();  // Display what's in the buffer (splashscreen)
    delay(1000);     // Delay 1000 ms
    oled.clear(PAGE); // Clear the buffer.
    
}

/**
 * Deconstructor
 */
Display::~Display(void)
{
    
}