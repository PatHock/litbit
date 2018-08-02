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
#include "../Rtc/Rtc.hpp"

const uint8_t deviceAddress = 0x50;

class Eeprom
{
    public:
        
        ~Eeprom(void); // Deconstructor
        
        // Returns the instance of EepromController
        static Eeprom* getInstance();
        
        // Initializes, since constructor cannot be called (to enforce singletons)
        void init(void);

        void printEntries(void);    // print all EEPROM logs to serial
        bool log(uint16_t steps);   // add an entry to the EEPROM
        bool eraseAllEntries(void); // ERASE EEPROM
        void readEntry(uint16_t address, uint32_t* unixTime, uint16_t* stepCount);

    
    private:
        Eeprom(void){};     // Constructor

        // Pointer to the single instance of Eeprom
        static Eeprom* _pInstance;

        uint16_t lastEntryAddr;
        uint32_t* entryUnixTime;
        uint16_t* stepCount;
        uint16_t deviceAddress = 0x50;
        void writeData(uint16_t dataAddress, uint32_t unixTime, uint16_t stepCount);

        
        
};

#endif  // EEPROM_HPP