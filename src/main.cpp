/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
  This example code is in the public domain.
 */

#include <Arduino.h>

int main(void) {
  //Initialise Arduino functionality.
  init();
   
  //Attach USB for applicable processors.
  #ifdef USBCON
    USBDevice.attach();
  #endif

  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(13, OUTPUT);

  while(true) {
    digitalWrite(13, HIGH);   // set the LED on
    delay(250);              // wait for a second
    digitalWrite(13, LOW);    // set the LED off
    delay(250);              // wait for a second
  }

  return 0;
}