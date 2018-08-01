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

#define ADXL_RANGE_2G 2
#define ADXL_RANGE_4G 4
#define ADXL_RANGE_8G 8
#define ADXL_RANGE_16G 16
#define ENABLE 1
#define DISABLE 0

class Accel
{
    public:
        // Destructor
        ~Accel(void); 

        // Returns the instance of EepromController
        static Accel* getInstance();

        // Initializes, since constructor cannot be called (to enforce singletons)
        void init(void);

        void printXYZ(void);    // used for ms4 step counting

        ADXL345* adxl; // public model (adxl library)  

        bool setAccelRange(uint8_t AdxlRange);

        void readAccel(int* accelArray);    // 1st index of accelArray is X, 2nd is Y, 3rd is Z

        int* accelArray;

    private:
        // Constructor
        Accel(void){};

        // Pointer to the single instance of EepromController 
        static Accel* _pInstance;

        uint8_t accelRange;

        float normalize(int16_t accelReading);


};

#endif  // ACCELCONTROLLER_HPP
