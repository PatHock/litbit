/**
 * Accel.cpp
 * ADXL345 Accelerometer Model Class
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#include "Accel.hpp"


/**
 * Constructor
 */
Accel::Accel(void) 
{

    adxl = ADXL345(); // Set accelerometer up for I2C operation
    adxl.powerOn();
    adxl.setRangeSetting(16); // Set reading range of 2, 4, 8 or 16 g
    adxl.setActivityXYZ(1, 0, 0);       // Set to activate movement detection in the axes "adxl.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
    adxl.setActivityThreshold(75);      // 62.5mg per increment   // Set activity   // Inactivity thresholds (0-255)
    adxl.setTimeInactivity(2);     // set inactivity timeout period, in seconds

    // Enable Interrupts (1 -> interrupt is enabled)
    adxl.InactivityINT(1);
    adxl.ActivityINT(1);

}

/**
 * Deconstructor
 */
Accel::~Accel(void) 
{
    
}

int Accel::getAccelX(void)
{
    int accel[3];
    adxl.readAccel(*(&accel));

    return accel[0];    // accel contains X(elem. 0), Y(elem. 1), Z (elem. 2)   
}

int Accel::getAccelY(void)
{
    int accel[3];
    adxl.readAccel(*(&accel));

    return accel[1];    // accel contains X(elem. 0), Y(elem. 1), Z (elem. 2)
}

int Accel::getAccelZ(void)
{
    int accel[3];
    adxl.readAccel(*(&accel));

    return accel[2];    // accel contains X(elem. 0), Y(elem. 1), Z (elem. 2)
}