/**
 * Eeprom.cpp
 * 24FC1025 EEPROM Controller-model Class
 * 
 * Patrick Hock 
 * August 1, 2018
 */

#include "Eeprom.hpp"

Eeprom *Eeprom::_pInstance = NULL;

/**
 * Initialization
 */
void Eeprom::init(void)
{
    // read lastEntryAddress
    Rtc = Rtc::getInstance();
    unixTime = 0;
    stepCount = 0;

    // if EEPROM is empty, take up the first two bytes with the address of the
    // last entry

    readLastEntryAddr();
    if (lastEntryAddr == 0)
    {
        writeLastEntryAddr(0x01);
    }
    // writeData(0x20, Rtc->getDateTime()->unixtime(), 4569);
    // readEntry(0x20);
    // Serial.print("test: ");
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
    readLastEntryAddr();
    for (int i = 0x01; i < lastEntryAddr; i += 6)
    {
        readEntry(i + 1);
        Serial.print(unixTime);
        Serial.print(", ");
        Serial.println(stepCount);
    }
}

/** 
 * @brief  Writes (timestamp, step) entry to eeprom
 * @note   Retrieves current time (unixtime) from RTC
 * @param  Steps: uint16_t representing the number of steps in this 15-minute time interval
 * @retval True if data is read back from Eeprom, and matches what was written
 */
bool Eeprom::log(uint16_t steps)
{
    // Figure out where the end of the last data entry was
    readLastEntryAddr();

    // write timestamp + step count to Eeprom
    writeData(lastEntryAddr + 1, Rtc->getDateTime()->unixtime(), steps);

    //update address of last data logged
    writeLastEntryAddr(lastEntryAddr + 6);

    return 1;
}

/** 
 * @brief  Erases entire Eeprom
 * @note   Actually only erases the first half but it is fine
 * @retval 
 */
bool Eeprom::eraseAllEntries(void)
{
    // look in datasheet on how to erase. Otherwise, write 0x0 to all addresses
    // read entire EEPROM, return true if all entries are 0x0

    for (uint16_t startAddr = 0; startAddr <= 0xFF7F; startAddr += 128) //0x1ff7f
    {
        Wire.beginTransmission((uint8_t)0x50);   // initiate transaction
        Wire.write((uint8_t)(startAddr >> 8));   // First half of 16 - bit address
        Wire.write((uint8_t)(startAddr & 0xFF)); // second half

        for (int i = 0; i < 128; i++)
        {
            Wire.write((uint8_t)0x0);
        }

        Wire.endTransmission(); // Nothing's wrong it's fine
        delay(5);               // Allow time for write to occur - write should not be followed immediately by a read
    }

    return true;
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

    Wire.requestFrom((uint8_t)0x50, (uint8_t)6);
    for (int i = 0; i < 6; i++)
    {
        if (Wire.available())
        {
            buffer[i] = (uint8_t)Wire.read();
        }
    }

    unixTime = ((uint32_t)buffer[0] << 24) | ((uint32_t)buffer[1] << 16) | ((uint32_t)buffer[2] << 8) | (uint32_t)buffer[3];
    stepCount = ((uint16_t)buffer[4] << 8) | (uint16_t)buffer[5];
    // Serial.println(unixTime);   // (DEBUGGING)
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
    Wire.write((uint8_t)(unixTime >> 24));  // first 8 bits of unixtime
    Wire.write((uint8_t)(unixTime >> 16));  // second 8 bits of unixtime
    Wire.write((uint8_t)(unixTime >> 8));   // third 8 bits of unixtime
    Wire.write((uint8_t)(unixTime & 0xFF)); // last 8 bits of unixtime

    Wire.write((uint8_t)(stepCount >> 8));   // first 8 bits of stepCount
    Wire.write((uint8_t)(stepCount & 0xFF)); // second 8 bits of stepCount

    Wire.endTransmission(); // Nothing's wrong it's fine
    delay(5);               // Allow time for write to occur - write should not be followed immediately by a read
}

void Eeprom::readLastEntryAddr(void)
{
    Wire.beginTransmission((uint8_t)deviceAddress); // initiate transaction

    Wire.write((uint8_t)0x0); // First half of 16 - bit address
    Wire.write((uint8_t)0x0); // second half

    Wire.endTransmission();

    Wire.requestFrom((uint8_t)0x50, (uint8_t)2);
    for (int i = 0; i < 2; i++)
    {
        if (Wire.available())
        {
            buffer[i] = (uint8_t)Wire.read();
        }
    }

    lastEntryAddr = ((uint16_t)buffer[0] << 8) | (uint16_t)buffer[1];
}

void Eeprom::writeLastEntryAddr(uint16_t addr)
{
    Wire.beginTransmission((uint8_t)deviceAddress); // initiate transaction

    Wire.write((uint8_t)0x0); // First half of 16 - bit address
    Wire.write((uint8_t)0x0); // second half

    // lastEntryAddr resides in the first two bytes
    Wire.write((uint8_t)(addr << 8));   // first 8 bits
    Wire.write((uint8_t)(addr & 0xFF)); // second 8 bits

    Wire.endTransmission(); // Nothing's wrong it's fine
    delay(5);               // Allow time for write to occur
}

/** 
 * @brief  Erases all entries and resets last entry addr
 * @note   
 * @retval None
 */
void Eeprom::resetEeprom(void)
{
    eraseAllEntries();
    writeLastEntryAddr(0x01);
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
Eeprom *Eeprom::getInstance()
{
    if (!_pInstance)
    {
        _pInstance = new Eeprom();
    }

    return _pInstance;
}