/**
 * Accel.hpp
 * ADXL345 Accelerometer
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#ifndef ACCEL_HPP
#define ACCEL_HPP

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
        Accel(void);     // Constructor
        ~Accel(void); // Deconstructor

        int16_t getAccelX(void);
        int16_t getAccelY(void);
        int16_t getAccelZ(void);

        bool setAccelRange(uint8_t AdxlRange);


    private:
        ADXL345 adxl;

};

#endif  // ACCEL_HPP