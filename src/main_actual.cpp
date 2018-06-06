// /**
//  * Main.cpp
//  * 
//  * Patrick Hock 
//  * June 4, 2018
//  */

// #include <stdint.h>
// #include <Arduino.h>
// #include <avr/interrupt.h>
// #include <avr/sleep.h>
// #include <avr/power.h>

// #include "Controller/Controller.hpp"

// #define SERIAL_SPEED 9600

// int main(void)
// {

//   //IMPORTANT - Init code below is necessary for board to function properly
//   init();

//   #ifdef USBCON
//     USBDevice.attach();
//   #endif

//   #ifdef __AVR_ATmega32U4__
//     delay(3000); // wait 3 seconds for the serial connection
//   #endif

//   pinMode(LED_BUILTIN, OUTPUT);
//   set_sleep_mode(SLEEP_MODE_PWR_DOWN);

//   Serial.begin(SERIAL_SPEED);

  // while(!Serial) {
  //   ;
  // }

//   Serial.println("Itsy Bitsy Initialized.");

//   // Create controller singletons
//   AccelController *AccelC    =  AccelController::getInstance();
//   EepromController *EepromC  =  EepromController::getInstance();
//   I2cController *I2cC        =  I2cController::getInstance();
//   RtcController *RtcC        =  RtcController::getInstance();

//   // Initialize controllers
//   AccelC  ->  init();
//   EepromC ->  init();
//   I2cC    ->  init();
//   RtcC    ->  init();

//   while (true)
//   {
//     digitalWrite(LED_BUILTIN, HIGH); // set the LED on
//     delay(250);                      // wait for a second
//     digitalWrite(LED_BUILTIN, LOW);  // set the LED off
//     delay(250);                      // wait for a second

//     // clock_prescale_set(clock_div_4);
//     // // power save
//     // cli();  // Disable global interrupts
//     // if(true) {
//     //   // power_all_disable;
//     //   sleep_enable();
//     //   sei();  // Enable global interrupts
//     //   sleep_cpu();
//     //   sleep_disable();
//     // }
//     // sei();
//   }

//   return 0;
// }
