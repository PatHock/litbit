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

#define DISPLAY_DC 1
#define DISPLAY_RST 9

class Display
{
    public:
        ~Display(void); // Deconstructor
        
        // Returns the instance of Display
        static Display* getInstance();

        void init(void);
    
    private:
        Display(void){};     // Constructor

        // Pointer to the single instance of DisplayController 
        static Display* _pInstance;

        

};

#endif  // DISPLAY_HPP