/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
  This example code is in the public domain.
 */

#include <Arduino.h>

int main(void) {
  
  //IMPORTANT - Init code below is necessary for board to function properly
  init();
  // Needed for ATMEGA32u4 processors
  #ifdef USBCON
    USBDevice.attach();
  #endif

  pinMode(LED_BUILTIN, OUTPUT);

  while(true) {
    digitalWrite(13, HIGH);   // set the LED on
    delay(250);              // wait for a second
    digitalWrite(13, LOW);    // set the LED off
    delay(250);              // wait for a second
  }

  return 0;
}