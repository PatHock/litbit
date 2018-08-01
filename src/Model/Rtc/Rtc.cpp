/**
 * Rtc.cpp
 * MCP7490N Real-time-clock Model Class
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#include "Rtc.hpp"

/**
 * Constructor
 */
Rtc::Rtc(void) 
{
    // Establish connection with MCP7940N
    MCP7940.begin();
    // if(MCP7940.begin())
    //     Serial.println(F("MCP7940N found."));
    // else
    //     Serial.println(F("Unable to find MCP7940N."));
    
    // Enable oscillator
    // if(!MCP7940.deviceStatus())
    // {
    //     Serial.println(F("Oscillator is off, turning it on."));
    //     if(!MCP7940.deviceStart())
    //         Serial.println(F("Oscillator did not start."));
    // } 

    MCP7940.deviceStatus();
    MCP7940.deviceStart();

    MCP7940.adjust();  

    // Serial.println(F("MCP7940N initialized."));
}

/**
 * Deconstructor
 */
Rtc::~Rtc(void) 
{

}

DateTime Rtc::getDateTime() 
{
    return MCP7940.now();
}

// void Rtc::setWeekday()
// {
//     MCP7940.
// }

//     // Use argument DateTime to manually set time, or 
//     // leave blank to set time to the time when the program
//     // was compiled
//     rtc.adjust(currentDateTime);   