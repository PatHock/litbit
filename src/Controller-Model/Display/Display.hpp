/**
 * Display.hpp
 * Sparkfun Micro OLED Breakout Controller-model (Qwiic)
 * 
 * Patrick Hock 
 * August 1, 2018
 */

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Arduino.h>
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library
#include <Wire.h>
#include "../../Constants/Port.hpp"
#include <WString.h>

// #define DISPLAY_DC 1
// #define DISPLAY_RST 9
const uint8_t DISPLAY_TIMEOUT = 3;  // Timeout in seconds

class Display
{
    public:
        ~Display(void); // Deconstructor
        
        // Returns the instance of Display
        static Display* getInstance();

        void init(void);

        void printText(String title);
        void clear(void);
        void enable(void);
        void disable(void);

        
    
    private:
        Display(void){};     // Constructor

        // Pointer to the single instance of DisplayController 
        static Display* _pInstance;
        

        

        

};

#endif  // DISPLAY_HPP