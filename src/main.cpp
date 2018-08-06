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

// FIXME: These flags are spaghet and you should be ashamed
volatile bool alarmFlag = 0;
volatile bool adxlFlag = 0;


void ISR_Rtc_Alarm() 
{
  noInterrupts();
  alarmFlag = 1;
  interrupts();
}

void ISR_Adxl()
{
  noInterrupts();
  adxlFlag = 1;
  interrupts();
}


int main(void){

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


  Serial.begin(SERIAL_SPEED);

  // Don't allow startup until serial is available
  while(!Serial) {
    ;
  }

  
  /*
    Interrupt and pin mode assignments
  */
  pinMode(PIN_RTC_MFP, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_RTC_MFP), ISR_Rtc_Alarm, FALLING);

  pinMode(PIN_ACCEL_INT_2, INPUT);
  attachPCINT(digitalPinToPCINT(PIN_ACCEL_INT_2), ISR_Adxl, RISING);
  // attachInterrupt(digitalPinToInterrupt(PIN_ACCEL_INT_2), ISR_Adxl, RISING);
  

  // Get controller-model instances
  I2c* I2c = I2c::getInstance();
  Accel* Accel = Accel::getInstance();
  Rtc* Rtc = Rtc::getInstance();
  Eeprom* Eeprom = Eeprom::getInstance();
  Display* Display = Display::getInstance();
  // Ble* Ble = Ble::getInstance();

  // Initialize controller-models
  I2c -> init();
  Rtc -> init();
  Eeprom -> init(); // make sure this one is AFTER the RTC
  Display -> init();   // Display might not work now
  Accel -> init();
  // Ble -> init();




  
  // Rtc -> setTimer(10);

  while (1)
  {
    //FIXME: more flag spaghet below
    if(alarmFlag)
    {
      noInterrupts();
      alarmFlag = 0;
      interrupts();

      Serial.println("Alarm triggered.");
    }

    Serial.println(adxlFlag);

    if(adxlFlag)
    {
      noInterrupts();
      adxlFlag = 0;
      interrupts();

      Serial.println("ADXL interrupt occurred.");
    }

    Serial.println(digitalRead(PIN_ACCEL_INT_2));
    Serial.println(Accel -> adxl -> getInterruptSource(), BIN);

    

    delay(1000);

    // Accel -> printXYZ();
    // Rtc -> printTimeToSerial();

    // delay(1000);
  
    
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



