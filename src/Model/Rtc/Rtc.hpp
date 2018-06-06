/**
 * Rtc.hpp
 * MCP7490N Real-time-clock
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#ifndef RTC_HPP
#define RTC_HPP

#include <Arduino.h>
#include <MCP7940.h>

class Rtc 
{
    public:
        Rtc(void);     // Constructor
        ~Rtc(void); // Destructor

        DateTime getDateTime();
        void setDateTime();

    private:
        MCP7940_Class MCP7940;

};

#endif  //RTC_HPP