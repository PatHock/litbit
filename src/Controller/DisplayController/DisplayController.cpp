/**
 * DisplayController.cpp
 * Sparkfun Micro OLED Breakout (Qwiic)
 * 
 * Patrick Hock 
 * June 26, 2018
 */

#include "DisplayController.hpp"

DisplayController* DisplayController::_pInstance = NULL;

/**
 * Deconstructor
 */
DisplayController::~DisplayController(void)
{
    delete DisplayModel;   
}
/**
 * Initialization
 */
void DisplayController::init(void)
{
    DisplayModel = new Display();
}

/**
 * Singleton Manager
 */
DisplayController* DisplayController::getInstance()
{
    if(!_pInstance) 
    {
        _pInstance = new DisplayController();
    }

    return _pInstance;
}