/**
 * Accel.cpp
 * ADXL345 Accelerometer Controller-Model Class
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#include "Accel.hpp"

Accel *Accel::_pInstance = NULL;

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
    
    // Enable link bit, sample rate 1hz, Measure mode
    writeToAddress(ADXL345_POWER_CTL, ADXL_MEASURE_BIT | ADXL_LINK_BIT | ADXL_WAKEUP_1HZ); 

    setAccelRange(accelRange);
    adxl->set_bw(0x7);             // 12.5 Hz
    adxl->setInterruptLevelBit(0); // interrupts are active high

    adxl->setActivityThreshold(22);   // 62.5mg per increment (verify that this is true)
    adxl->setActivityXYZ(1, 1, 1);    // Enable activity detection in all axes
    adxl->setTimeInactivity(3);       // set inactivity timeout period, in seconds
    adxl->setInactivityThreshold(18); // Set inactivity threshold, 62.5mg per increment
    adxl->setInactivityXYZ(1, 1, 1);  // Enable inactivity detection

    readFromAddress(ADXL345_POWER_CTL);
    writeToAddress(ADXL345_POWER_CTL, adxlReg | ADXL_AUTO_ASLEEP_BIT);  // Enable auto sleep for ADXL

    // adxl -> setTapThreshold(50);           // mg per incrementadxl.setTapThreshold(50);
    // adxl -> setTapDuration(15);            // 625 μs per incrementadxl.setTapDuration(15);
    // adxl -> setDoubleTapLatency(80);       // 1.25 ms per increment
    // adxl -> setDoubleTapWindow(200);       // 1.25 ms per increment
    // adxl -> setTapDetectionOnXYZ(true, true, true);

    writeToAddress(ADXL345_INT_MAP, 0x2);              //map watermark to INT2 pin
    adxl->setImportantInterruptMapping(1, 2, 1, 1, 2); // map double tap, inactivity to INT2

    setupFIFO(ADXL_FIFO_MODE_FIFO, ADXL_WATERMARK_SIZE); // Set watermark to 30 samples, FIFO mode

    writeToAddress(ADXL345_INT_ENABLE, 0x2); // Enable watermark interrupt
    adxl->InactivityINT(1);                  // Enable Inactivity Interrupt
    adxl->ActivityINT(1);                    // Enable Activity Interrupt
}

/**
 * Singleton Manager
 */
Accel *Accel::getInstance()
{
    if (!_pInstance)
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
    adxl->readAccel(accelArray);
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

    if (accelRange == 2 || accelRange == 4 || accelRange == 8 || accelRange == 16)
    {
        adxl->setRangeSetting(accelRange);
        isValidRange = true;
    }

    return isValidRange;
}

void Accel::readAccel(int *accelArray)
{
    adxl->readAccel(accelArray);
}

void Accel::setupFIFO(uint8_t mode, uint8_t watermark)
{
    // Set the mode and watermark
    writeToAddress((uint8_t)0x38, ((uint8_t)(mode << 6) | (uint8_t)(watermark & 0x1F)) & ~(uint8_t)(0x20));
}

void Accel::readFromAddress(uint8_t addr)
{
    Wire.beginTransmission((uint8_t)0x53); // Begin transmission with ADXL
    Wire.write((uint8_t)addr);             // Slave address to be read from
    Wire.endTransmission();

    Wire.beginTransmission((uint8_t)0x53);
    Wire.requestFrom((uint8_t)0x53, 1); // Request 1 Byte

    if (Wire.available())
    {
        adxlReg = Wire.read();
    }

    Wire.endTransmission();
}

void Accel::writeToAddress(uint8_t addr, uint8_t data)
{
    Wire.beginTransmission((uint8_t)0x53);
    Wire.write(addr); // Slave address to be written to

    Wire.write(data);
    Wire.endTransmission();
}

void Accel::readFifo(void)
{

    for (int i = 0; i < ADXL_WATERMARK_SIZE; i++)
    {
        Wire.beginTransmission((uint8_t)0x53); // Begin transmission with ADXL
        Wire.write((uint8_t)0x32);             // 0x32 is DATAX0
        Wire.endTransmission();

        Wire.beginTransmission((uint8_t)0x53);
        Wire.requestFrom((uint8_t)0x53, 6); // Request 6 Bytes

        // Read X, Y, Z values from I2c
        for (int j = 0; j < 6; j++)
        {
            if (Wire.available())
            {
                sampleBuffer[j] = Wire.read();
            }
        }

        Wire.endTransmission();

        // Piece bytes together
        for (int j = 0; j < 3; j++)
        {
            rawSample[j] = (int16_t)((((int16_t)sampleBuffer[2 * j + 1]) << 8) | sampleBuffer[2 * j]);
        }

        // do magnitude calculation
        sampleMagnitude[i] = (int16_t)sqrt(rawSample[0] * rawSample[0] + rawSample[1] * rawSample[1] + rawSample[2] * rawSample[2]);
    }
    adxl->getInterruptSource(); // reading this seems to allow for the water mark interrupt to happen
}

void processStepCount(void)
{
}
