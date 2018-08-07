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
    adxl -> set_bw(0x8); // 25 Hz?

    adxl -> setActivityXYZ(1,1,1);  // Enable activity detection in all axes
    adxl -> setActivityThreshold(40);   // 62.5mg per increment (verify that this is true)
    adxl -> setTimeInactivity(2);   // set inactivity timeout period, in seconds
    adxl -> setTapThreshold(50);           //  mg per incrementadxl.setTapThreshold(50);           // 62.5 mg per incrementsetTapThreshold(50);           // 62.5 mg per increment
    adxl -> setTapDuration(15);            // 625 μs per incrementadxl.setTapDuration(15);            // 625 μs per incrementsetTapDuration(15);            // 625 μs per increment
    adxl -> setDoubleTapLatency(80);       // 1.25 ms per increment
    adxl -> setDoubleTapWindow(200);       // 1.25 ms per increment

    adxl -> setTapDetectionOnXYZ(true, true, true);

    adxl -> setImportantInterruptMapping(1,2,1,2,1);
    readFromAddress(0x2F);
    writeToAddress(0x2F, (uint8_t)(adxlReg | 0x2)); //map watermark to INT2 pin

    adxl -> setInterruptLevelBit(0);    // interrupts are active high

    setupFIFO(ADXL_FIFO_MODE_FIFO, ADXL_WATERMARK_SIZE);  // Set watermark to 30 samples, FIFO mode

    // Enable interrups (1 ---> enable)
    adxl -> InactivityINT(0);
    adxl -> ActivityINT(1);
    adxl -> FreeFallINT(0);
    adxl -> doubleTapINT(0);
    adxl -> singleTapINT(0);
    // readFromAddress(0x2E);
    // writeToAddress(0x2E, (uint8_t)(adxlReg | 0x2)); //Enable watermark interrupt

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

void Accel::setupFIFO(uint8_t mode, uint8_t watermark)
{
    // Set the mode and watermark
    // 0x1 << 5: Set trigger bit to 0 (disables trigger interrupt on INT pin 2)
    writeToAddress((uint8_t)0x38, ((uint8_t)(mode << 5) | (uint8_t)(watermark & 0x1F)) & (uint8_t)(0x20));
}

void Accel::readFromAddress(uint8_t addr)
{
    Wire.beginTransmission((uint8_t)0x53);  // Begin transmission with ADXL
    Wire.write((uint8_t)addr);  // Slave address to be read from
    Wire.endTransmission();

    Wire.beginTransmission((uint8_t)0x53);
    Wire.requestFrom((uint8_t)0x53, 1);  // Request 1 Byte

    if(Wire.available())
    {
        adxlReg = Wire.read();
    }

    Wire.endTransmission();
}

void Accel::writeToAddress(uint8_t addr, uint8_t data)
{
    Wire.beginTransmission((uint8_t)0x53);
    Wire.write(addr);  // Slave address to be written to

    Wire.write(data);  
    Wire.endTransmission();
}

void Accel::readFifo(void)
{
    
    // Serial.println(millis());

    for(int i=0; i<ADXL_WATERMARK_SIZE; i++)
    {
        Wire.beginTransmission((uint8_t)0x53);  // Begin transmission with ADXL
        Wire.write((uint8_t)0x32);  // 0x32 is DATAX0
        Wire.endTransmission();

        Wire.beginTransmission((uint8_t)0x53);
        Wire.requestFrom((uint8_t)0x53, 6);  // Request 6 Bytes

        // Read X, Y, Z values from I2c
        for(int j=0; j<6; j++)
        {
            if(Wire.available())
            {
                sampleBuffer[j] = Wire.read();
            }
        }

        Wire.endTransmission();

        // Piece bytes together 
        for(int j=0; j<3; j++)
        {
            rawSample[j] = (int16_t)((((int16_t)sampleBuffer[2*j + 1]) << 8) | sampleBuffer[2*j]);
            // Serial.println(rawSample[j]);
        }

        // do magnitude calculation
        sampleMagnitude[i] = (int16_t)sqrt(rawSample[0]*rawSample[0] + rawSample[1]*rawSample[1] + rawSample[2]*rawSample[2]);
        // Serial.println(sampleMagnitude[i]);
        // delayMicroseconds(5);
    }
    // readFromAddress(0x39);
    // Serial.println(adxlReg, BIN);
    // Serial.println(millis());
}

void processStepCount(void)
{

}

