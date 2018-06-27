/**
 * BleController.hpp
 * nRF8001 Controller header file
 * 
 * Patrick Hock
 * June 26, 2018
 */

#ifndef BLECONTROLLER_HPP
#define BLECONTROLLER_HPP

#include <Arduino.h>
#include "Model/Ble/Ble.hpp"


class BleController
{
    public:
        //Deconstructor
        ~BleController(void);

        // Returns the instance of BleController
        static BleController* getInstance();

        void init(void);

    private:
        //Constructor
        BleController(void){};

        // Pointer to the single instance of BleController 
        static BleController* _pInstance;

        Ble* BleModel;

};

#endif  // BLECONTROLLER_HPP