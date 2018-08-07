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
volatile byte adxlInterrupts = 0x0;


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
    Pin mode assignments
  */
  pinMode(PIN_RTC_MFP, INPUT);
  pinMode(PIN_ACCEL_INT_2, INPUT);

  // Get controller-model instances
  I2c* I2c = I2c::getInstance();
  Accel* Accel = Accel::getInstance();
  Rtc* Rtc = Rtc::getInstance();
  Eeprom* Eeprom = Eeprom::getInstance();
  // Display* Display = Display::getInstance();
  // Ble* Ble = Ble::getInstance();

  // Initialize controller-models
  I2c -> init();
  Rtc -> init();
  Eeprom -> init(); // make sure this one is AFTER the RTC
  Accel -> init();
  // Display -> init();   // Display might not work now
  // Ble -> init();
  
  attachPCINT(digitalPinToPCINT(PIN_ACCEL_INT_2), ISR_Adxl, RISING);  // used PCINT pin
  // Attach interrupts
  attachInterrupt(digitalPinToInterrupt(PIN_RTC_MFP), ISR_Rtc_Alarm, FALLING);
  

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

    if(adxlFlag)
    {
      noInterrupts();
      adxlFlag = 0;
      interrupts();
      adxlInterrupts = Accel -> adxl -> getInterruptSource();  // needed to clear interrupt on PCINT pin
            
      if((adxlInterrupts >> 7) & 0x01)
        Serial.print("ADXL Data Ready  ");

      if((adxlInterrupts >> 6) & 0x01)
        Serial.print("ADXL Single Tap  ");

      if((adxlInterrupts >> 5) & 0x01)
        Serial.print("ADXL Double Tap  ");

      if((adxlInterrupts >> 4) & 0x01)
        Serial.print("ADXL Activity  ");

      if((adxlInterrupts >> 3) & 0x01)
        Serial.print("ADXL Inactivity  ");

      if((adxlInterrupts >> 2) & 0x01)
        Serial.print("ADXL Free Fall  ");

      if((adxlInterrupts >> 1) & 0x01)
      {
        Serial.print("ADXL Water Mark  ");
        Accel -> readFifo();
        // Accel -> readFifo();
        // adxl readsamples function here
      }

      if(adxlInterrupts & 0x01)
        Serial.print("ADXL Overrun  ");
      
      // adxlInterrupts = Accel -> adxl -> getInterruptSource();  // needed to clear interrupt on PCINT pin
      // Serial.println(adxlInterrupts, BIN);
      Serial.println();

    }

    // Accel -> readFromAddress(0x39);
    // Serial.println(Accel -> adxlReg, BIN);
    // Serial.println(digitalRead(PIN_ACCEL_INT_2));

    // adxlInterrupts = Accel -> adxl -> getInterruptSource();  // needed to clear interrupt on PCINT pin
    // Serial.println(adxlInterrupts, BIN);

    // Accel -> readFromAddress(0x39);
    // Serial.println(Accel -> adxlReg, BIN);
    // Accel -> printXYZ();
    // Rtc -> printTimeToSerial();

    // delay(100);

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



