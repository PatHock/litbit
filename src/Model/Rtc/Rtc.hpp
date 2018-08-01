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

#define MONTH_JAN 1
#define MONTH_FEB 2
#define MONTH_MAR 3
#define MONTH_APR 4
#define MONTH_MAY 5
#define MONTH_JUN 6
#define MONTH_JLY 7
#define MONTH_AUG 8
#define MONTH_SEP 9
#define MONTH_OCT 10
#define MONTH_NOV 11
#define MONTH_DEC 12

class Rtc 
{
    public:
        Rtc(void);     // Constructor
        ~Rtc(void); // Destructor

        DateTime getDateTime();
        void setDateTime();
        bool getAlarmState(const uint8_t alarmNumber);
        bool clearAlarm(const uint8_t alarmNumber);
        bool setAlarm(const uint8_t alarmNumber, const uint8_t alarmType,
                const DateTime dt, const bool state = true );
        bool isAlarm(const uint8_t alarmNumber);


    private:
        MCP7940_Class MCP7940;

};

#endif  //RTC_HPP