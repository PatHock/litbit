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

#include "Controller-Model/Controller-Model.hpp"

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

  clock_prescale_set(clock_div_1);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  Serial.begin(SERIAL_SPEED);

  // Don't allow startup until serial is available
  while(!Serial) {
    ;
  }

  // Get controller-model instances
  Accel* Accel = Accel::getInstance();
  Rtc* Rtc = Rtc::getInstance();

  // Initialize controller-models
  Accel -> init();
  Rtc -> init();

  while (1)
  {

    Accel -> printXYZ();
    Rtc -> printTimeToSerial();

    delay(1000);
  
    
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
