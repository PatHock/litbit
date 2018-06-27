/**
 * AccelController.cpp
 * ADXL345 Accelerometer Controller Class
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#include "AccelController.hpp"

AccelController* AccelController::_pInstance = NULL;

/**
 * Deconstructor
 */
AccelController::~AccelController(void) 
{
    delete AccelModel;
}

/**
 * Initialization
 */
void AccelController::init(void)
{
    AccelModel = new Accel();
}

/**
 * Singleton Manager
 */
AccelController* AccelController::getInstance()
{
    if(!_pInstance) 
    {
        _pInstance = new AccelController();
    }

    return _pInstance;
}