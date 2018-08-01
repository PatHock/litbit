/**
 * RtcController.cpp
 * MCP7490N Real-time-clock Controller Class
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#include "RtcController.hpp"

RtcController* RtcController::_pInstance = NULL;

/**
 * Deconstructor
 */
RtcController::~RtcController(void)
{
    delete RtcModel;
}

/**
 * Initialization
 */
void RtcController::init(void)
{
    RtcModel = new Rtc();
}

/**
 * Singleton Manager
 */
RtcController* RtcController::getInstance()
{
        if(!_pInstance) 
    {
        _pInstance = new RtcController();
    }

    return _pInstance;
}

void RtcController::printTimeToSerial(void) 
{
    DateTime now = RtcModel->getDateTime();
    Serial.println(now.unixtime());
    // Serial.print(" ");
    // Serial.print(now.day());
    // Serial.print(now.month());
    // Serial.print(" ");
    // Serial.print(now.day());
    // Serial.print(" , ");
    // Serial.print(now.year());
    // Serial.print("   ");
    // Serial.print(now.hour());
    // Serial.print(":");
    // Serial.print(now.minute());
    // Serial.print(":");
    // Serial.print(now.second());
    // Serial.println("");
}