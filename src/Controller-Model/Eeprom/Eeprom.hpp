/**
 * Eeprom.hpp
 * 24FC1025 EEPROM
 * 
 * Patrick Hock 
 * August 1, 2018
 */

#ifndef EEPROM_HPP
#define EEPROM_HPP

#include <Arduino.h>

class Eeprom
{
    public:
        
        ~Eeprom(void); // Deconstructor
        
        // Returns the instance of EepromController
        static Eeprom* getInstance();
        
        // Initializes, since constructor cannot be called (to enforce singletons)
        void init(void);

    
    private:
        Eeprom(void){};     // Constructor

        // Pointer to the single instance of Eeprom
        static Eeprom* _pInstance;
        
};

#endif  // EEPROM_HPP