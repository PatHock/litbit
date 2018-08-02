/**
 * Ble.cpp
 * nRF8001 controller-model class
 * 
 * Patrick Hock
 * August 1, 2018
 */

#include "Ble.hpp"

Ble* Ble::_pInstance = NULL;

/**
 * Initialization
 */
void Ble::init(void)
{
    
}

/**
 * Singleton Manager
 */
Ble* Ble::getInstance()
{
    if(!_pInstance) 
    {
        _pInstance = new Ble();
    }

    return _pInstance;
}

/**
 * Deconstructor
 */
Ble::~Ble(void)
{
    
}