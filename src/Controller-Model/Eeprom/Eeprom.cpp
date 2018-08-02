/**
 * Eeprom.cpp
 * 24FC1025 EEPROM Controller-model Class
 * 
 * Patrick Hock 
 * August 1, 2018
 */

#include "Eeprom.hpp"

Eeprom* Eeprom::_pInstance = NULL;

/**
 * Initialization
 */
void Eeprom::init(void)
{
    // read lastEntryAddress
    Rtc* Rtc = Rtc::getInstance();
    writeData((uint16_t)0x0, Rtc ->getDateTime()->unixtime(), 345);
    // readEntry((uint16_t)0x0, entryUnixTime, stepCount);
    // Serial.print("unix time + step count: ");
    // Serial.print(*entryUnixTime);
    // Serial.print(", ");
    // Serial.println(*stepCount);

}

/** 
 * @brief  Prints all EEPROM (time, steps) log entries to the serial terminal
 * @note   Iterates from first entry to the last one written.
 * @retval None
 */
void Eeprom::printEntries(void)
{
    // read last addr written, loop 
}

/** 
 * @brief  Writes (timestamp, step) entry to eeprom
 * @note   Retrieves current time (unixtime) from RTC
 * @param  Steps: uint16_t representing the number of steps in this 15-minute time interval
 * @retval True if data is read back from Eeprom, and matches what was written
 */
bool Eeprom::log(uint16_t steps)
{
    // get time from rtc
    // figure out where to write entry to 
    // write to eeprom
    // read from eeprom, if it is the same as what was written, return true
    return 0;
}

/** 
 * @brief  Erases entire Eeprom
 * @note   
 * @retval True if every address of Eeprom reads (0)
 */
bool Eeprom::eraseAllEntries(void)
{
    // look in datasheet on how to erase. Otherwise, write 0x0 to all addresses
    // read entire EEPROM, return true if all entries are 0x0
    return 0;
}

/** 
 * @brief  Reads an entry from the Eeprom, given an address.
 * @note   
 * @param  address: 16-bit address to read from
 * @param  unixTime: pointer to a 32-bit uint. Entry unixtime is written here.
 * @param  stepCount: pointer to 16-bit uint stepcount. Entry step count value is written here.
 * @retval None
 */
void Eeprom::readEntry(uint16_t address, uint32_t* unixTime, uint16_t* stepCount)
{
    Wire.beginTransmission((uint8_t)deviceAddress); // initiate transaction

    Wire.write((uint8_t)(address >> 8));   // First half of 16 - bit address
    Wire.write((uint8_t)(address & 0xFF)); // second half

    Wire.endTransmission();

    for (int i = 0; i < 5; i++)
    {
        Wire.requestFrom((uint8_t)0x50, (uint8_t)1);
        if (Wire.available())
        {
            switch (i) 
            {
                case 0: *unixTime = (Wire.read() << 24);
                case 1: *unixTime &= (Wire.read() << 16);
                case 2: *unixTime &= (Wire.read() << 8);
                case 3: *unixTime &= Wire.read();
                case 4: *stepCount = (Wire.read() << 8);
                case 5: *stepCount &= Wire.read();
            }
        }
    }
}

/** 
 * @brief  
 * @note   Per datasheet, successive write operations are sequential in memory
 * @param  address: 
 * @param  unixTime: 
 * @param  stepCount: 
 * @retval None
 */
void Eeprom::writeData(uint16_t dataAddress, uint32_t unixTime, uint16_t stepCount)
{
    Wire.beginTransmission((uint8_t)0x50); // initiate transaction

    Wire.write((uint8_t)(dataAddress >> 8));   // First half of 16 - bit address
    Wire.write((uint8_t)(dataAddress & 0xFF)); // second half

    // four wire.writes for unixtime, two for step count
    Wire.write((uint8_t)((unixTime >> 24) & 0xFF)); // first 8 bits of unixtime
    Wire.write((uint8_t)((unixTime >> 16) & 0xFF)); // first 8 bits of unixtime
    Wire.write((uint8_t)((unixTime >> 8) & 0xFF)); // first 8 bits of unixtime
    Wire.write((uint8_t)(unixTime & 0xFF)); // first 8 bits of unixtime

    Wire.write((uint8_t)(stepCount >> 8)); // first 8 bits of unixtime
    Wire.write((uint8_t)(unixTime& 0xFF)); // first 8 bits of unixtime

    Wire.endTransmission(); // Nothing's wrong it's fine
    delay(5);               // Allow time for write to occur - write should not be followed immediately by a read
}



/**
 * Deconstructor
 */
Eeprom::~Eeprom(void)
{
    delete entryUnixTime;
    delete stepCount;
}

/**
 * Singleton Manager
 */
Eeprom* Eeprom::getInstance()
{
    if(!_pInstance) 
    {
        _pInstance = new Eeprom();
    }

    return _pInstance;
}

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