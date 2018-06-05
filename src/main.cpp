/**
 * Main.cpp
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#include <main.hpp> // Change name eventually

int main(void) {
  clock_prescale_set(clock_div_4);
  
  //IMPORTANT - Init code below is necessary for board to function properly
  init();
  // Needed for ATMEGA32u4 processors
  #ifdef USBCON
    USBDevice.attach();
  #endif

  pinMode(LED_BUILTIN, OUTPUT);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  
  while(true) {
    digitalWrite(LED_BUILTIN, HIGH);   // set the LED on
    delay(250);              // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // set the LED off
    delay(250);              // wait for a second

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
