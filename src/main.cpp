/**
 * Main.cpp
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#include <stdint.h>
#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>

#include <SparkFun_ADXL345.h>
#include <MCP7940.h>

#define ADXL_RANGE_2G 2
#define ADXL_RANGE_4G 4
#define ADXL_RANGE_8G 8
#define ADXL_RANGE_16G 16
#define ENABLE 1
#define DISABLE 0

/*
 * Required Data structures for Demo. May be replaced at a later date
 */
typedef struct
{
    int x, y, z;
} Accel;

/**
 * Get your global variables here, folks.
 */
ADXL345 adxl;
Accel currentReading;
DateTime currentDateTime;
MCP7940_Class rtc;

/**
 * Setup and Initialization functions
 */

/**
* Function implements any configuration necessary to operate
* on the SPI bus
*/
void setupSPI() {}

/**
* Function implements any configuration necessary to operate
* on the i2c bus
*/
void setupI2C()
{
    Wire.begin();
}

/*
* Conduct any initialization necessary of the ADXL345
* either internally to Arduino or external in the peripheral
*/
void setupADXL345()
{
    // initialize for I2c communication
    adxl = ADXL345();
    adxl.powerOn();

    adxl.setRangeSetting(ADXL_RANGE_2G); // Set reading range to 16 G's
    adxl.setActivityXYZ(0, 0, 1);        // Set to be activated from activity on X Y or Z axes
    adxl.setActivityThreshold(75);       // scaled 0-255, 255 is full scale of the range

    // Turn on Interrupts for each mode (1 == ON, 0 == OFF)
    adxl.ActivityINT(1);
}

/**
* Conduct any initialization necessary of the RTC
* either internally to Arduino or external in the peripheral
* Initialize the current date/time in MM/DD/YY HH:MM:SS format
*/
void setupRTC()
{
    // Establish connection with MCP7940N
    if (rtc.begin())
        Serial.println(F("MCP7940N found."));
    else
        Serial.println(F("Unable to find MCP7940N."));

    // Enable oscillator
    if (!rtc.deviceStatus())
    {
        Serial.println(F("Oscillator is off, turning it on."));

        if (!rtc.deviceStart())
            Serial.println(F("Oscillator did not start."));
    }

    rtc.adjust();

    Serial.println(F("MCP7940N initialized."));
}

/**
* Conduct any initialization necessary of the EERPOM
* either internally to Arduino or external in the peripheral
*/
void setupEEPROM()
{
}

/**
 * Data read/write functions
 */

/**
 * Function takes a pointer to an Accel data object
 * and populates the contents with the X, Y, and Z acceleration values.
 * Value may be raw readings or normalized relative to 0g.
 */
void readAcceleration(Accel *data)
{
    adxl.readAccel(&data->x, &data->y, &data->z);

}

/**
 * Function takes a pointer to a DateTime object and
 * populates with the current DateTime in MM/DD/YYYY HH:MM:SS
 * format. Return values must be human readable
 */
void readDateTime(DateTime *data)
{
    *data = rtc.now();
}

/**
 * Function writes a series of uint16_t values to the EEPROM
 * from the data array. Length of array is specified by the len parameter.
 * All writing is assumed to occur at EEPROM storage address 0x0.
 * Any existing data should be overwritten.
 */
void writeDataToEEPROM(uint16_t *data, uint16_t len) {}

/**
 * Function reads a sequence of uint16_t values from the EEPROM
 * and stores the result in the buffer array. Length of buffer is
 * specified by the len parameter. All reads are assumed to begin at EEPROM storage
 * address 0x0.
 */
void readDataFromEEPROM(uint16_t *buffer, uint16_t len) {}

/**
  * typical sample code for your milestone. Particular
  * implementations may be different if you are in a different
  * development environment
  */
void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        ;
    }
    
    /*
   * Configure all buses
   */
    setupI2C();
    setupSPI();

    /**
  * Initialize the EEPROM
  */
    // setupEEPROM();

    /**
   * Configure the ADXL345
   */
    setupADXL345();

    setupRTC();

    
}

void loop()
{
    /**
   * Test #1: Try to read from the ADXL345 and
   * print out the results
   */
    readAcceleration(&currentReading);

    Serial.print(currentReading.x);
    Serial.print("\t");
    Serial.print(currentReading.y);
    Serial.print("\t");
    Serial.println(currentReading.z);

    /**
   * Test #2: Try to read out the time of day and
   * print out the results
   */
       readDateTime(&currentDateTime);
       Serial.print(currentDateTime.month());
       Serial.print("/");
       Serial.print(currentDateTime.day());
       Serial.print("/");
       Serial.print(currentDateTime.year());
       Serial.print("\t");
       Serial.print(currentDateTime.hour());
       Serial.print(":");
       Serial.print(currentDateTime.minute());
       Serial.print(":");
       Serial.println(currentDateTime.second());

    /**
    * Test #3: Try to write and read back some
    * random data
    */
    // uint16_t array[5];
    // for(int i=0;i<5;i++)
    // {
    //   array[i]=random();
    // }
    // writeDataToEEPROM(array,5);

    // uint16_t buffer[5];

    // readDataFromEEPROM(buffer,5);

    // bool testPass = true;
    // for(int i=0;i<5;i++)
    // {
    // 	if(buffer[i]!=array[i])
    // 	{
    // 		testPass=false;
    // 	}
    // }

    // if(testPass)
    // {
    // 	Serial.println("EEPROM Test Passed.");
    // }
    // else
    // {
    // 	Serial.println("EEPROM Test Failed.");
    // }

    delay(1000);
}
