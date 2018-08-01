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
    adxl.setActivityXYZ(ENABLE, DISABLE, DISABLE);       // Set to activate movement detection in the axes "adxl.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
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

/** 
 * @brief  Returns raw accel reading
 * @note   
 * @retval raw acceleration value in X axis, scaled such that the maximum 
 * and minimum values +/- 1024 represent the ADXL range in Gs
 */
int16_t Accel::getAccelX(void)
{
    int accel[3];
    adxl.readAccel(*(&accel));

    return accel[0];    // accel contains X(elem. 0), Y(elem. 1), Z (elem. 2)   
}

/** 
 * @brief  
 * @note   
 * @retval raw acceleration value in Y axis, scaled such that the maximum 
 * and minimum values +/- 1024 represent the ADXL range in Gs
 */
int16_t Accel::getAccelY(void)
{
    int accel[3];
    adxl.readAccel(*(&accel));

    return accel[1];    // accel contains X(elem. 0), Y(elem. 1), Z (elem. 2)
}

/** 
 * @brief  
 * @note   
 * @retval raw acceleration value in Y axis, scaled such that the maximum 
 * and minimum values +/- 1024 represent the ADXL range in Gs
 */
int16_t Accel::getAccelZ(void)
{
    int accel[3];
    adxl.readAccel(*(&accel));

    return accel[2];    // accel contains X(elem. 0), Y(elem. 1), Z (elem. 2)
}

/** 
 * @brief  Sets the full-scale range for the ADXL345
 * @note   
 * @param  accelRange: The acceleration (in Gs) represented by the full scale 
 * of the Accelerometer (+/- 1024). 2, 4, 8, and 16 are the only valid values.
 * @retval boolean  - true if range set successfully, false otherwise.
 */
bool Accel::setAccelRange(uint8_t accelRange)
{
    bool isValidRange = false;

    if(accelRange == 2 || accelRange == 4 || accelRange == 8 || accelRange == 16)
    {
        adxl.setRangeSetting(accelRange);
        isValidRange = true;
    }
    
    return isValidRange;
}