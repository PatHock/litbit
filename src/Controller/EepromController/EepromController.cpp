/**
 * EepromController.cpp
 * 24FC1025 EEPROM Controller Class
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#include "EepromController.hpp"

EepromController* EepromController::_pInstance = NULL;


/**
 * Deconstructor
 */
EepromController::~EepromController(void) 
{
    delete EepromModel;
}

/**
 * Initialization
 */
void EepromController::init(void)
{
    EepromModel = new Eeprom();
}

/**
 * Singleton Manager
 */
EepromController* EepromController::getInstance()
{
    if(!_pInstance) 
    {
        _pInstance = new EepromController();
    }

    return _pInstance;
}

// /**
//  * Function reads a sequence of uint16_t values from the EEPROM
//  * and stores the result in the buffer array. Length of buffer is
//  * specified by the len parameter. All reads are assumed to begin at EEPROM storage
//  * address 0x0.
//  */
// void readDataFromEEPROM(uint8_t *buffer, uint16_t len)
// {
//     uint16_t dataAddress = 0x0;
//     uint16_t deviceAddress = 0x50;

//     Wire.beginTransmission((uint8_t)deviceAddress); // initiate transaction

//     Wire.write((uint8_t)(dataAddress >> 8));   // First half of 16 - bit address
//     Wire.write((uint8_t)(dataAddress & 0xFF)); // second half

//     Wire.endTransmission();

//     for (int i = 0; i < len; i++)
//     {
//         Wire.requestFrom((uint8_t)0x50, (uint8_t)1);
//         if (Wire.available())
//         {
//             buffer[i] = Wire.read();
//         }
//     }
// }

// /**
//  * Function writes a series of uint16_t values to the EEPROM
//  * from the data array. Length of array is specified by the len parameter.
//  * All writing is assumed to occur at EEPROM storage address 0x0.
//  * Any existing data should be overwritten.
//  */
// void writeDataToEEPROM(uint8_t *data, uint8_t len)
// {
//     uint16_t dataAddress = 0x0;
//     uint16_t deviceAddress = 0x50;

//     Wire.beginTransmission((uint8_t)deviceAddress); // initiate transaction

//     Wire.write((uint8_t)(dataAddress >> 8));   // First half of 16 - bit address
//     Wire.write((uint8_t)(dataAddress & 0xFF)); // second half

//     for (int i = 0; i < len; i++)
//     {
//         // Per datasheet, successive write operations are sequential in memory
//         Wire.write((uint8_t)data[i]);
//     }

//     Wire.endTransmission(); // Nothing's wrong it's fine
//     delay(5);               // Allow time for write to occur - write should not be followed immediately by a read
// }