/**
 * Rtc.cpp
 * MCP7490N Real-time-clock Class
 * 
 * Patrick Hock 
 * Aug 1, 2018
 */

#include "Rtc.hpp"

Rtc* Rtc::_pInstance = NULL;


/**
 * Initialization
 */
void Rtc::init(void)
{
    MCP7940 = new MCP7940_Class();
    now = new DateTime();

    // Establish connection with MCP7940N
    MCP7940 -> begin();

    MCP7940 -> deviceStatus();
    MCP7940 -> deviceStart();
    MCP7940 -> adjust();  
    
    now = getDateTime();
}

/** 
 * @brief  
 * @note   
 * @param  seconds: Number of seconds in the future when alarm should
 *         go off 
 * @retval 
 */
bool Rtc::setTimer(uint32_t seconds)
{
    // MCP7940 -> clearAlarm(0);
    return MCP7940 -> setAlarm(0, ALARM_TYPE_ALL, DateTime(now -> unixtime() + seconds), 1);
}

/**
 * Deconstructor
 */
Rtc::~Rtc(void) 
{
    delete MCP7940;
}

DateTime* Rtc::getDateTime() 
{
    *now = MCP7940 -> now();
    return now;
}

/**
 * Singleton Manager
 */
Rtc* Rtc::getInstance()
{
        if(!_pInstance) 
    {
        _pInstance = new Rtc();
    }

    return _pInstance;
}

void Rtc::printTimeToSerial(void) 
{
    getDateTime();
    Serial.println(now -> unixtime());
    // Serial.print(" ");
    // Serial.print(now -> day());
    // Serial.print(now -> month());
    // Serial.print(" ");
    // Serial.print(now -> day());
    // Serial.print(" , ");
    // Serial.print(now -> year());
    // Serial.print("   ");
    // Serial.print(now -> hour());
    // Serial.print(":");
    // Serial.print(now -> minute());
    // Serial.print(":");
    // Serial.print(now -> second());
    // Serial.println("");
}


// Commented out spaghet below

// void Rtc::setWeekday()
// {
//     MCP7940.
// }

//     // Use argument DateTime to manually set time, or 
//     // leave blank to set time to the time when the program
//     // was compiled
//     rtc.adjust(currentDateTime);   