/**
 * AccelController.cpp
 * ADXL345 Accelerometer Controller Class
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#include "AccelController.hpp"

AccelController* AccelController::_pInstance = NULL;

/**
 * Deconstructor
 */
AccelController::~AccelController(void) 
{
    delete accelModel;
}

/**
 * Initialization
 */
void AccelController::init(void)
{
    accelRange = ADXL_RANGE_4G;
    accelModel = new Accel();
    accelModel -> setAccelRange(accelRange);
}

/**
 * Singleton Manager
 */
AccelController* AccelController::getInstance()
{
    if(!_pInstance) 
    {
        _pInstance = new AccelController();
    }

    return _pInstance;
}


/** 
 * @brief  Serial Print function 
 * @note   Used for ms4 step counting. Outputs X, Y, Z acceleration
 * to serial terminal in CSV format.
 * @retval None
 */
void AccelController::printXYZ(void)
{
    Serial.print(normalize(accelModel->getAccelX()));
    Serial.print(",");
    Serial.print(normalize(accelModel->getAccelY()));
    Serial.print(",");
    Serial.println(normalize(accelModel->getAccelZ()));
}

/** 
 * @brief  Scales acceleration readings so that 1 represents 1 G of acceleration (9.8 m/s^2)
 * @note   
 * @param  accelReading: Raw acceleration value from accelerometer
 * @retval Normalized acceleration reading, 1 = 1G
 */
float AccelController::normalize(int16_t accelReading)
{
    return (float)(accelReading * accelRange) / (float)512;
}

