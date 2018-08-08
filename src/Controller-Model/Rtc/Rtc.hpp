/**
 * Rtc.hpp
 * MCP7490N Real-time-clock
 * 
 * Patrick Hock 
 * August 1, 2018
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

const uint8_t ALARM_TYPE_SECS = 0;
const uint8_t ALARM_TYPE_MINS = 1;
const uint8_t ALARM_TYPE_HOURS = 2;
const uint8_t ALARM_TYPE_DAYOFWEEK = 3;
const uint8_t ALARM_TYPE_DATE = 4;
const uint8_t ALARM_TYPE_ALL = 7;

const uint8_t ALARM_PERIOD_SECONDS = 900;   // 15 minute time interval


class Rtc 
{
    public:
        
        ~Rtc(void); // Destructor

        // Returns the instance of Rtc
        static Rtc* getInstance();

        // Initializes, since constructor cannot be called (to enforce singletons)
        void init(void);

        // Prints time to the serial bus. Duh.
        void printTimeToSerial(void);

        DateTime* getDateTime();

        MCP7940_Class* MCP7940;

        bool setTimer(uint32_t seconds);



    private:
        
        Rtc(void){};     // Constructor

        // Pointer to the single instance of RTC
        static Rtc* _pInstance;

        DateTime* now;

};

#endif  //RTC_HPP