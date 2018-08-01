/**
 * AccelController.hpp
 * ADXL345 Accelerometer
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#ifndef ACCELCONTROLLER_HPP
#define ACCELCONTROLLER_HPP

#include <stdint.h>
#include <Arduino.h>
#include <SparkFun_ADXL345.h>
#include "Model/Accel/Accel.hpp"

class AccelController 
{
    public:
        // Destructor
        ~AccelController(void); 

        // Returns the instance of EepromController
        static AccelController* getInstance();

        // Initializes, since constructor cannot be called (to enforce singletons)
        void init(void);

        void printXYZ(void);    // used for ms4 step counting

    private:
        // Constructor
        AccelController(void){};

        // Pointer to the single instance of EepromController 
        static AccelController* _pInstance;

        Accel* accelModel;

        uint8_t accelRange;

        float normalize(int16_t accelReading);


};

#endif  // ACCELCONTROLLER_HPP
