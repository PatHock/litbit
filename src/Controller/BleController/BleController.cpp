/**
 * BleController.cpp
 * nRF8001 Controller Class
 * 
 * Patrick Hock
 * June 26, 2018
 */

#include "BleController.hpp"

BleController* BleController::_pInstance = NULL;


/**
 * Deconstructor
 */
BleController::~BleController(void) 
{
    delete BleModel;
}

/**
 * Initialization
 */
void BleController::init(void)
{
    BleModel = new Ble();
}

/**
 * Singleton Manager
 */
BleController* BleController::getInstance()
{
    if(!_pInstance) 
    {
        _pInstance = new BleController();
    }

    return _pInstance;
}