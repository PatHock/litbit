/**
 * Main.cpp
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#include <Arduino.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>

#include "Controller/Controller.hpp"

#define SERIAL_SPEED 14400

int main(void)
{

  //IMPORTANT - Init code below is necessary for board to function properly
  init();

  #ifdef USBCON
    USBDevice.attach();
  #endif

  #ifdef __AVR_ATmega32U4__
    delay(3000); // wait 3 seconds for the serial connection
  #endif

  pinMode(LED_BUILTIN, OUTPUT);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  Serial.begin(SERIAL_SPEED);

  while(!Serial) {
    ;
  }

  Serial.println("Itsy Bitsy Initialized.");

  // Create controller singletons
  I2cController *I2cC        =  I2cController::getInstance();
  AccelController *AccelC    =  AccelController::getInstance();
  EepromController *EepromC  =  EepromController::getInstance();
  RtcController *RtcC        =  RtcController::getInstance();
  DisplayController* DisplayC = DisplayController::getInstance();


  // Initialize controllers
  I2cC    ->  init(); 
  AccelC  ->  init(); 
  EepromC ->  init(); //TODO: Migrate functionality
  RtcC    ->  init(); 
  DisplayC -> init();


  while (true)
  {
    // digitalWrite(LED_BUILTIN, HIGH); // set the LED on
    // delay(250);                      // wait for a second
    // digitalWrite(LED_BUILTIN, LOW);  // set the LED off
    // delay(250);                      // wait for a second

    AccelC->printXYZ();
    delay(20);  // Should give a sample rate of approx. 50 Hz

    // clock_prescale_set(clock_div_4);
    // // power save
    // cli();  // Disable global interrupts
    // if(true) {
    //   // power_all_disable;
    //   sleep_enable();
    //   sei();  // Enable global interrupts
    //   sleep_cpu();
    //   sleep_disable();
    // }
    // sei();
  }

  return 0;
}



// void loop()
// {
//     /**
//    * Test #1: Try to read from the ADXL345 and
//    * print out the results
//    */
//     readAcceleration(&currentReading);

//     Serial.println("--------------------------------------------------");
//     Serial.print("Accelerometer X, Y, Z readings (in Gs): ");
//     Serial.print((float)(currentReading.x + 1)/256);
//     Serial.print("\t");
//     Serial.print((float)(currentReading.y + 1)/256);
//     Serial.print("\t");
//     Serial.println((float)(currentReading.z + 1)/256);

//     /**
//    * Test #2: Try to read out the time of day and
//    * print out the results
//    */
//     readDateTime(&currentDateTime);
//     Serial.print(currentDateTime.month());
//     Serial.print("/");
//     Serial.print(currentDateTime.day());
//     Serial.print("/");
//     Serial.print(currentDateTime.year());
//     Serial.print("\t");
//     Serial.print(currentDateTime.hour());
//     Serial.print(":");
//     Serial.print(currentDateTime.minute());
//     Serial.print(":");
//     Serial.println(currentDateTime.second());

//     /**
//     * Test #3: Try to write and read back some
//     * random data
//     */
//     uint8_t array[5];
//     for (int i = 0; i < 5; i++)
//     {
//         array[i] = random();
//     }

//     writeDataToEEPROM(array, 5);
//     uint8_t buffer[5];

//     Serial.print("Written to EEPROM: \t");
//     Serial.print(array[0]);
//     Serial.print("\t");
//     Serial.print(array[1]);
//     Serial.print("\t");
//     Serial.print(array[2]);
//     Serial.print("\t");
//     Serial.print(array[3]);
//     Serial.print("\t");
//     Serial.println(array[4]);

//     readDataFromEEPROM(buffer, 5);

//     Serial.print("Read from EEPROM: \t");
//     Serial.print(buffer[0]);
//     Serial.print("\t");
//     Serial.print(buffer[1]);
//     Serial.print("\t");
//     Serial.print(buffer[2]);
//     Serial.print("\t");
//     Serial.print(buffer[3]);
//     Serial.print("\t");
//     Serial.println(buffer[4]);

//     bool testPass = true;
//     for (int i = 0; i < 5; i++)
//     {
//         if (buffer[i] != array[i])
//         {
//             testPass = false;
//         }
//     }

//     if (testPass)
//     {
//         Serial.println("EEPROM Test Passed.");
//     }
//     else
//     {
//         Serial.println("EEPROM Test Failed.");
//     }

//     delay(1000);
// }
