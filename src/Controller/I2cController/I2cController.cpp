/**
 * I2cController.cpp
 * 
 * Patrick Hock 
 * June 5, 2018
 */

#include "I2cController.hpp"

I2cController* I2cController::_pInstance = NULL;


/**
 * Deconstructor
 */
I2cController::~I2cController(void) 
{
    delete I2cModel;
}

/**
 * Initialization
 */
void I2cController::init(void)
{
    I2cModel = new I2c();
    Wire.setClock(I2C_FREQ);
    Wire.begin();
}

/**
 * Singleton Manager
 */
I2cController* I2cController::getInstance()
{
    if(!_pInstance) 
    {
        _pInstance = new I2cController();
    }

    return _pInstance;
}
