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

volatile bool alarmFlag = 0;

void ISR_Rtc_Alarm() 
{
  noInterrupts();
  alarmFlag = 1;
  interrupts();
}

int main(void)
{

  //IMPORTANT - Init code below is necessary for board to function properly
  init();
  clock_prescale_set(clock_div_1);

  #ifdef USBCON
    USBDevice.attach();
  #endif

  #ifdef __AVR_ATmega32U4__
    delay(3000); // wait 3 seconds for the serial connection
  #endif

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  /*
    Interrupt and pin mode assignments
  */
  pinMode(PIN_RTC_MFP, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_RTC_MFP), ISR_Rtc_Alarm, FALLING);


  Serial.begin(SERIAL_SPEED);

  // Don't allow startup until serial is available
  while(!Serial) {
    ;
  }

 
  // Get controller-model instances
  I2c* I2c = I2c::getInstance();
  Accel* Accel = Accel::getInstance();
  Rtc* Rtc = Rtc::getInstance();
  Eeprom* Eeprom = Eeprom::getInstance();
  Display* Display = Display::getInstance();
  Ble* Ble = Ble::getInstance();

  // Initialize controller-models
  I2c -> init();
  Rtc -> init();
  Eeprom -> init();
  Display -> init();
  Accel -> init();
  Ble -> init();

  
  Rtc -> setTimer(10);

  while (1)
  {
    if(alarmFlag)
    {
      noInterrupts();
      alarmFlag = 0;
      interrupts();

      Serial.println("Alarm triggered.");
    }

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
