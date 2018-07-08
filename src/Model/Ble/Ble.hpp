/**
 * Ble.hpp
 * nRF8001 model header file
 * 
 * Patrick Hock
 * June 26, 2018
 */

#ifndef BLE_HPP
#define BLE_HPP

#include <Arduino.h>
#include <BLEPeripheral.h>
#include "../Constants/Port.hpp"

class Ble
{
    public:
        Ble(void);     // Constructor
        ~Ble(void); // Destructor

        void reset();


        
    private:


};
#endif // BLE_HPP