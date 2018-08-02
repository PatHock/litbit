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
    unixTime = 0;
    stepCount = 0;

    // writeData((uint16_t)0x00, Rtc->getDateTime()->unixtime(), (uint16_t)346);
    // readEntry((uint16_t)0x00);
    // Serial.print("unix time + step count: ");
    // Serial.print(unixTime);
    // Serial.print(", ");
    // Serial.println(stepCount);

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
 * @retval None
 */
void Eeprom::readEntry(uint16_t address)
{
    Wire.beginTransmission((uint8_t)deviceAddress); // initiate transaction

    Wire.write((uint8_t)(address >> 8));   // First half of 16 - bit address
    Wire.write((uint8_t)(address & 0xFF)); // second half

    Wire.endTransmission();

    for (int i = 0; i < 6; i++)
    {
        Wire.requestFrom((uint8_t)0x50, (uint8_t)1);
        if (Wire.available())
        {
            buffer[i] = (uint8_t)Wire.read();
        }
    }

        unixTime = ((uint32_t)buffer[0] << 24) | ((uint32_t)buffer[1] << 16) | ((uint32_t)buffer[2] << 8) | buffer[3];
        stepCount = (uint16_t)buffer[4] << 8 | buffer[5];
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
    Wire.write((uint8_t)(unixTime >> 24)); // first 8 bits of unixtime
    Wire.write((uint8_t)(unixTime >> 16)); // second 8 bits of unixtime
    Wire.write((uint8_t)(unixTime >> 8)); // third 8 bits of unixtime
    Wire.write((uint8_t)(unixTime & 0xFF)); // last 8 bits of unixtime

    Wire.write((uint8_t)(stepCount >> 8)); // first 8 bits of stepCount
    Wire.write((uint8_t)(stepCount & 0xFF)); // second 8 bits of stepCount

    Wire.endTransmission(); // Nothing's wrong it's fine
    delay(5);               // Allow time for write to occur - write should not be followed immediately by a read
}



/**
 * Deconstructor
 */
Eeprom::~Eeprom(void)
{

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