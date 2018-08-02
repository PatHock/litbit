/**
 * I2c.cpp
 * 
 * Patrick Hock 
 * August 1, 2018
 */

#include "I2c.hpp"

I2c* I2c::_pInstance = NULL;

/**
 * Initialization
 */
void I2c::init(void)
{
    Wire.setClock(I2C_FREQ);
    Wire.begin();
}

/**
 * Deconstructor
 */
I2c::~I2c(void)
{

}

/**
 * Singleton Manager
 */
I2c* I2c::getInstance()
{
    if(!_pInstance) 
    {
        _pInstance = new I2c();
    }

    return _pInstance;
}