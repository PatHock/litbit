/**
 * Ble.hpp
 * nRF8001 controller-model header file
 * 
 * Patrick Hock
 * August 1, 2018
 */

#ifndef BLE_HPP
#define BLE_HPP

#include <Arduino.h>
#include <BLEPeripheral.h>
#include "../../Constants/Port.hpp"

class Ble
{
    public:
        
        ~Ble(void); // Destructor

        void reset();   // TODO: Check this out later

        // Returns the instance of BleController
        static Ble* getInstance();

        void init(void);
        
    private:
        Ble(void){};     // Constructor

        // Pointer to the single instance of BleController 
        static Ble* _pInstance;


};


#endif // BLE_HPP