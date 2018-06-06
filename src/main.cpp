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


// ADXL header
#include <SparkFun_ADXL345.h>
#define ADXL_RANGE_2G 2
#define ADXL_RANGE_4G 4
#define ADXL_RANGE_8G 8
#define ADXL_RANGE_16G 16
#define ENABLE 1
#define DISABLE 0

// RTC header
#include <MCP7940.h>
#define MONTH_JAN 1
#define MONTH_FEB 2
#define MONTH_MAR 3
#define MONTH_APR 4
#define MONTH_MAY 5
#define MONTH_JUN 6
#define MONTH_JLY 7
#define MONTH_AUG 8
#define MONTH_SEP 9
#define MONTH_OCT 10
#define MONTH_NOV 11
#define MONTH_DEC 12


// I2C header
#define I2C_FREQ 100000

/*
 * Required Data structures for Demo. May be replaced at a later date
 */
typedef struct
{
    int x, y, z;
} Accel;

/**
 * Get your global variables here, folks. :)
 */
ADXL345 adxl;
Accel currentReading;
DateTime currentDateTime = DateTime(2018, MONTH_JUN, 6, 14, 15, 0);
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
    Wire.setClock(I2C_FREQ);  // set I2C clock freq
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

    // Turn on Interrupts for Activity
    adxl.ActivityINT(ENABLE);
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

    // Use argument DateTime to manually set time, or 
    // leave blank to set time to the time when the program
    // was compiled
    rtc.adjust(currentDateTime);    

    Serial.println(F("MCP7940N initialized."));
}

/**
* Conduct any initialization necessary of the EERPOM
* either internally to Arduino or external in the peripheral
*/
void setupEEPROM()
{
    // Device address is 0x50
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
void writeDataToEEPROM(uint8_t *data, uint8_t len)
{
    uint16_t dataAddress = 0x0;
    uint16_t deviceAddress = 0x50;

    Wire.beginTransmission((uint8_t)deviceAddress); // initiate transaction

    Wire.write((uint8_t)(dataAddress >> 8));   // First half of 16 - bit address
    Wire.write((uint8_t)(dataAddress & 0xFF)); // second half

    for (int i = 0; i < len; i++)
    {
        // Per datasheet, successive write operations are sequential in memory
        Wire.write((uint8_t)data[i]);
    }

    Wire.endTransmission(); // Nothing's wrong it's fine
    delay(5);               // Allow time for write to occur - write should not be followed immediately by a read
}

/**
 * Function reads a sequence of uint16_t values from the EEPROM
 * and stores the result in the buffer array. Length of buffer is
 * specified by the len parameter. All reads are assumed to begin at EEPROM storage
 * address 0x0.
 */
void readDataFromEEPROM(uint8_t *buffer, uint16_t len)
{
    uint16_t dataAddress = 0x0;
    uint16_t deviceAddress = 0x50;

    Wire.beginTransmission((uint8_t)deviceAddress); // initiate transaction

    Wire.write((uint8_t)(dataAddress >> 8));   // First half of 16 - bit address
    Wire.write((uint8_t)(dataAddress & 0xFF)); // second half

    Wire.endTransmission();

    for (int i = 0; i < len; i++)
    {
        Wire.requestFrom((uint8_t)0x50, (uint8_t)1);
        if (Wire.available())
        {
            buffer[i] = Wire.read();
        }
    }
}

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
     * Initialize the EEPROMnce of one bus line in pF.
    2: As a transmitter, the device must provide an internal minimum delay time to bridge the undefined region (minimum
    300 ns) of the falling edge of SCL to avoid unintended generation of Start or Stop conditions.
    3: The combined TSP and VHYS specifications are due to new Schmitt Trigger inputs which provide improved noise spike
    suppression. This eliminates the need for
     */
    setupEEPROM();

    /**
   * Configure the ADXL34nce of one bus line in pF.
2: As a transmitter, the device must provide an internal minimum delay time to bridge the undefined region (minimum
300 ns) of the falling edge of SCL to avoid unintended generation of Start or Stop conditions.
3: The combined TSP and VHYS specifications are due to new Schmitt Trigger inputs which provide improved noise spike
suppression. This eliminates the need for
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

    Serial.println("--------------------------------------------------");
    Serial.print("Accelerometer X, Y, Z readings (in Gs): ");
    Serial.print((float)(currentReading.x + 1)/256);
    Serial.print("\t");
    Serial.print((float)(currentReading.y + 1)/256);
    Serial.print("\t");
    Serial.println((float)(currentReading.z + 1)/256);

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
    uint8_t array[5];
    for (int i = 0; i < 5; i++)
    {
        array[i] = random();
    }

    writeDataToEEPROM(array, 5);
    uint8_t buffer[5];

    Serial.print("Written to EEPROM: \t");
    Serial.print(array[0]);
    Serial.print("\t");
    Serial.print(array[1]);
    Serial.print("\t");
    Serial.print(array[2]);
    Serial.print("\t");
    Serial.print(array[3]);
    Serial.print("\t");
    Serial.println(array[4]);

    readDataFromEEPROM(buffer, 5);

    Serial.print("Read from EEPROM: \t");
    Serial.print(buffer[0]);
    Serial.print("\t");
    Serial.print(buffer[1]);
    Serial.print("\t");
    Serial.print(buffer[2]);
    Serial.print("\t");
    Serial.print(buffer[3]);
    Serial.print("\t");
    Serial.println(buffer[4]);

    bool testPass = true;
    for (int i = 0; i < 5; i++)
    {
        if (buffer[i] != array[i])
        {
            testPass = false;
        }
    }

    if (testPass)
    {
        Serial.println("EEPROM Test Passed.");
    }
    else
    {
        Serial.println("EEPROM Test Failed.");
    }

    delay(1000);
}
