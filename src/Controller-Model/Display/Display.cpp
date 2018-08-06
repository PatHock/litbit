/**
 * Display.cpp
 * Sparkfun Micro OLED Breakout (Qwiic)
 * 
 * Patrick Hock 
 * August 1, 2018
 */

#include "Display.hpp"

Display* Display::_pInstance = NULL;

/**
 * Initialization
 */
void Display::init(void)
{
    MicroOLED oled(PIN_DISPLAY_RST, PIN_DISPLAY_DC);    // Initialize the OLED
    oled.begin();    // Initialize the OLED
    oled.clear(ALL); // Clear the display's internal memory
    oled.display();  // Display what's in the buffer (splashscreen)
    delay(1000);     // Delay 1000 ms
    oled.clear(PAGE); // Clear the buffer.
}

/**
 * Singleton Manager
 */
Display* Display::getInstance()
{
    if(!_pInstance) 
    {
        _pInstance = new Display();
    }

    return _pInstance;
}

/**
 * Deconstructor
 */
Display::~Display(void)
{

}