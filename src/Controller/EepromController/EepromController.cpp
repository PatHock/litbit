/**
 * EepromController.cpp
 * 24FC1025 EEPROM Controller Class
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#include "EepromController.hpp"

EepromController* EepromController::_pInstance = NULL;


/**
 * Deconstructor
 */
EepromController::~EepromController(void) 
{
    delete EepromModel;
}

/**
 * Initialization
 */
void EepromController::init(void)
{
    EepromModel = new Eeprom();
}

/**
 * Singleton Manager
 */
EepromController* EepromController::getInstance()
{
    if(!_pInstance) 
    {
        _pInstance = new EepromController();
    }

    return _pInstance;
}