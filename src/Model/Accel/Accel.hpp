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

};

#endif  // ACCEL_HPP