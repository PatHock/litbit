/**
 * DisplayController.hpp
 * Sparkfun Micro OLED Breakout (Qwiic)
 * 
 * Patrick Hock 
 * June 26, 2018
 */

#ifndef DISPLAY_CONTROLLER_HPP
#define DISPLAY_CONTROLLER_HPP

#include <Arduino.h>
#include "Model/Display/Display.hpp"


class DisplayController
{
    public:
        //Deconstructor
        ~DisplayController(void);

        // Returns the instance of DisplayController
        static DisplayController* getInstance();

        void init(void);

    private:
        //Constructor
        DisplayController(void){};

        // Pointer to the single instance of DisplayController 
        static DisplayController* _pInstance;

        Display* DisplayModel;

};



#endif  // DISPLAY_CONTROLLER_HPP