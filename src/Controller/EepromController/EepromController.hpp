/**
 * EepromController.hpp
 * 24FC1025 EEPROM
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#ifndef EEPROMCONTROLLER_HPP
#define EEPROMCONTROLLER_HPP

#include <Arduino.h>
#include "Model/Eeprom/Eeprom.hpp"

class EepromController
{
    public:
        // Destructor
        ~EepromController(void); 

        // Returns the instance of EepromController
        static EepromController* getInstance();

        // Initializes, since constructor cannot be called (to enforce singletons)
        void init(void);
    
    private:
        // Constructor
        EepromController(void){};

        // Pointer to the single instance of EepromController 
        static EepromController* _pInstance;

        Eeprom* EepromModel;

};

#endif  // EEPROMCONTROLLER_HPP