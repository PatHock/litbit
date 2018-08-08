/**
 * Display.cpp
 * Sparkfun Micro OLED Breakout (Qwiic)
 * 
 * Patrick Hock 
 * August 1, 2018
 */

#include "Display.hpp"

Display* Display::_pInstance = NULL;

MicroOLED oled(PIN_DISPLAY_RST, PIN_DISPLAY_DC);    // Initialize the OLED
/**
 * Initialization
 */
void Display::init(void)
{
    
    oled.begin();    // Initialize the OLED
    oled.clear(ALL); // Clear the display's internal memory
    oled.display();  // Display what's in the buffer (splashscreen)
    // delay(1000);     // Delay 1000 ms
    oled.clear(PAGE); // Clear the buffer.
    printText("sHitBiT");
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
 * @brief  
 * @note   
 * @retval None
 */
void Display::clear(void)
{
    oled.clear(PAGE);
    oled.display();
}

/** 
 * @brief  
 * @note   
 * @param  str[10]: 
 * @retval None
 */
void Display::printText(String title)
{
    // oled.clear(PAGE);
    // for(int i=0; i<10; i++)
    // {
    //     oled.write();
    // }
    // oled.display();
    int middleX = oled.getLCDWidth() / 2;
    int middleY = oled.getLCDHeight() / 2;
    
    oled.clear(PAGE);
    oled.setFontType(1);
    // Try to set the cursor in the middle of the screen
    oled.setCursor(middleX - (oled.getFontWidth() * (title.length()/2)),
                    middleY - (oled.getFontWidth() / 2));
    // Print the title:
    oled.print(title);
    oled.display();
    delay(1500);
    oled.clear(PAGE);
}

void Display::enable(void)
{
    oled.command(DISPLAYON);
}

void Display::disable(void)
{
    oled.command(DISPLAYOFF);
}

/**
 * Deconstructor
 */
Display::~Display(void)
{

}