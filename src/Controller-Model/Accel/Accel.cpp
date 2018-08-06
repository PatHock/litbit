/**
 * AccelController.cpp
 * ADXL345 Accelerometer Controller Class
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#include "Accel.hpp"

Accel* Accel::_pInstance = NULL;

/**
 * Deconstructor
 */
Accel::~Accel(void) 
{
    delete adxl;
}

/**
 * Initialization
 */
void Accel::init(void)
{
    accelRange = ADXL_RANGE_4G;

    adxl = new ADXL345();
    adxl -> powerOn();
    setAccelRange(accelRange);

    adxl -> setActivityXYZ(1,1,1);  // Enable activity detection in all axes
    adxl -> setActivityThreshold(75);   // 62.5mg per increment (verify that this is true)
    adxl -> setTimeInactivity(2);   // set inactivity timeout period, in seconds

    adxl -> setTapThreshold(50);           // 62.5 mg per incrementadxl.setTapThreshold(50);           // 62.5 mg per incrementsetTapThreshold(50);           // 62.5 mg per increment
    adxl -> setTapDuration(15);            // 625 μs per incrementadxl.setTapDuration(15);            // 625 μs per incrementsetTapDuration(15);            // 625 μs per increment
    adxl -> setDoubleTapLatency(80);       // 1.25 ms per increment
    adxl -> setDoubleTapWindow(200);       // 1.25 ms per increment

    adxl -> setTapDetectionOnXYZ(true, true, true);

    

    adxl -> setImportantInterruptMapping(2,2,2,2,2);
    adxl -> setInterruptLevelBit(0);

    // Enable interrups (1 ---> enable)
    adxl -> InactivityINT(0);
    adxl -> ActivityINT(0);
    adxl -> FreeFallINT(0);
    adxl -> doubleTapINT(1);
    adxl -> singleTapINT(0);

    // Serial.println(adxl -> getInterruptSource(), BIN);
    // Serial.println(adxl -> getInterruptSource(0), BIN);
    // Serial.println(adxl -> getInterruptSource(1), BIN);
    // Serial.println(adxl -> getInterruptSource(2), BIN);
    // Serial.println(adxl -> getInterruptSource(3), BIN);
    // Serial.println(adxl -> getInterruptSource(4), BIN);
    // Serial.println(adxl -> getInterruptSource(5), BIN);
    // Serial.println(adxl -> getInterruptSource(6), BIN);

    

}

/**
 * Singleton Manager
 */
Accel* Accel::getInstance()
{
    if(!_pInstance) 
    {
        _pInstance = new Accel();
    }

    return _pInstance;
}


/** 
 * @brief  Serial Print function 
 * @note   Used for ms4 step counting. Outputs X, Y, Z acceleration
 * to serial terminal in CSV format.
 * @retval None
 */
void Accel::printXYZ(void)
{
    adxl -> readAccel(accelArray);
    Serial.print(normalize(accelArray[0]), 4);
    Serial.print(",");
    Serial.print(normalize(accelArray[1]), 4);
    Serial.print(",");
    Serial.println(normalize(accelArray[2]), 4);
}

/** 
 * @brief  Scales acceleration readings so that 1 represents 1 G of acceleration (9.8 m/s^2)
 * @note   
 * @param  accelReading: Raw acceleration value from accelerometer
 * @retval Normalized acceleration reading, 1 = 1G
 */
float Accel::normalize(int16_t accelReading)
{
    return (float)(accelReading * accelRange) / (float)512;
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
        adxl->setRangeSetting(accelRange);
        isValidRange = true;
    }
    
    return isValidRange;
}

void Accel::readAccel(int* accelArray)
{
    adxl->readAccel(accelArray);
}