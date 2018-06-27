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
        ~Accel(void); // Destructor
        
    private:
        /*
        * Required Data structures for Demo. May be replaced at a later date
        */
        typedef struct
        {
        uint16_t x, y, z;
        } Acceleration;

        ADXL345 adxl;

};

#endif  // ACCEL_HPP