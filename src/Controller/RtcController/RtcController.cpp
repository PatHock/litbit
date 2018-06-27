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