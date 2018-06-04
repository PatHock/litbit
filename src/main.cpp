/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
  This example code is in the public domain.
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

// /**
//    setup() executes once at boot
// */


// void setup() {
//   clock_prescale_set(clock_div_4);
//   power_adc_disable();
//   //configure on-board LED as OUTPUT
//   pinMode(13, OUTPUT);

//   //Initialize Serial/UART for 9600 baud
//   // Serial.begin(9600);


//   //print a message to know we're alive
//   // Serial.println("Hello world!");

//   /**
//      Place a long delay here so that the device is not always asleep.
//      Failure to do so will cause the device to "brick" and you cannot
//      re-program via the SPI bootloader
//   */
//   delayLoop();
// }

// /**
//    A delay function that blinks the LED while a count down is going on
// */
// void delayLoop()
// {
//   // Serial.println("Begin the count down!");
//   long startTime = millis();
//   const long totalDelay = 5000;

//   bool timeExpired = (millis() - startTime) > totalDelay;
//   while (!timeExpired)
//   {
// //    digitalWrite(13, HIGH);
//     delay(200);
// //    digitalWrite(13, LOW);
// //    delay(100);

//     timeExpired = (millis() - startTime) > totalDelay;
//   }
  
// }

// /**
//    loop is executed continuously
// */
// void loop() {

//   /**
//      Follow the process in the ATMEL documentation to do to sleep.
//      Try out different sleep modes.
//      https://www.microchip.com/webdoc/AVRLibcReferenceManual/group__avr__sleep.html

//     The 5 different modes are:
//             SLEEP_MODE_IDLE
//             SLEEP_MODE_ADC
//             SLEEP_MODE_PWR_SAVE
//             SLEEP_MODE_STANDBY
//             SLEEP_MODE_PWR_DOWN
//   */

 
//   //set the desired sleep mode
//   set_sleep_mode(SLEEP_MODE_PWR_DOWN);

//   //stop interrupts (execute atomically)
//   cli();

//   /**
//      Follow the code template from the AVR Sleep
//      documentation
//   */
//   boolean someCondition = true;
//   if (someCondition)
//   {

//     //print message and delay so serial is flushed.
//     //Otherwise message will not complete
//     // Serial.println("Good night!");
//     // Serial.flush();
//     delay(1000);
    
//     power_all_disable();
//     //enable sleep mode by setting the sleep bit
//     sleep_enable();

//     //re-enable interrupts. If you do not, then you will never
//     //awake from sleep...
// //    sei();

//     //execute the sleep instruction and actually go to sleep
//     sleep_cpu();

//     //WAKE UP! First thing to do is disable sleep so we
//     //don't do it again.
//     sleep_disable();
//   }

//   //restore interrupts now that processor is awake
//   sei();

//   //Print a message saying you're back!
//   // Serial.println("I'm alive!");

//   //delay again before entering sleep
//   delayLoop();
// }