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
// #include "Model/Ble/Ble.hpp"    //TODO: move 
// #include "Model/Display/Display.hpp" //TODO: move


// // // ADXL header
// // #include <SparkFun_ADXL345.h>
// // #define ADXL_RANGE_2G 2
// // #define ADXL_RANGE_4G 4
// // #define ADXL_RANGE_8G 8
// // #define ADXL_RANGE_16G 16
// // #define ENABLE 1
// // #define DISABLE 0

// // // RTC header
// // #include <MCP7940.h>
// // #define MONTH_JAN 1
// // #define MONTH_FEB 2
// // #define MONTH_MAR 3
// // #define MONTH_APR 4
// // #define MONTH_MAY 5
// // #define MONTH_JUN 6
// // #define MONTH_JLY 7
// // #define MONTH_AUG 8
// // #define MONTH_SEP 9
// // #define MONTH_OCT 10
// // #define MONTH_NOV 11
// // #define MONTH_DEC 12


// // // I2C header
// // #define I2C_FREQ 100000

// /*
//  * Required Data structures for Demo. May be replaced at a later date
//  */
// typedef struct
// {
//     int x, y, z;
// } Accel;

// /**
//  * Get your global variables here, folks. :)
//  */
// // ADXL345 adxl;
// Accel currentReading;
// // DateTime currentDateTime = DateTime(2018, MONTH_JUN, 6, 14, 25, 0);
// // MCP7940_Class rtc;


// /**
//  * Setup and Initialization functions
//  */

// /**
// * Function implements any configuration necessary to operate
// * on the SPI bus
// */
// void setupSPI() {}

// // /**
// // * Function implements any configuration necessary to operate
// // * on the i2c bus
// // */
// // void setupI2C()
// // {
// //     Wire.setClock(I2C_FREQ);  // set I2C clock freq
// //     Wire.begin();
// // }

// /*
// * Conduct any initialization necessary of the ADXL345
// * either internally to Arduino or external in the peripheral
// */
// void setupADXL345()
// {
//     // initialize for I2c communication
//     adxl = ADXL345();
//     adxl.powerOn();

//     adxl.setRangeSetting(ADXL_RANGE_2G); // Set reading range to 16 G's
//     adxl.setActivityXYZ(0, 0, 1);        // Set to be activated from activity on X Y or Z axes
//     adxl.setActivityThreshold(75);       // scaled 0-255, 255 is full scale of the range

//     // Turn on Interrupts for Activity
//     adxl.ActivityINT(ENABLE);
// }

// /**
// * Conduct any initialization necessary of the RTC
// * either internally to Arduino or external in the peripheral
// * Initialize the current date/time in MM/DD/YY HH:MM:SS format
// */
// void setupRTC()
// {
//     // Establish connection with MCP7940N
//     if (rtc.begin())
//         Serial.println(F("MCP7940N found."));
//     else
//         Serial.println(F("Unable to find MCP7940N."));

//     // Enable oscillator
//     if (!rtc.deviceStatus())
//     {
//         Serial.println(F("Oscillator is off, turning it on."));

//         if (!rtc.deviceStart())
//             Serial.println(F("Oscillator did not start."));
//     }

//     // Use argument DateTime to manually set time, or 
//     // leave blank to set time to the time when the program
//     // was compiled
//     rtc.adjust(currentDateTime);    

//     Serial.println(F("MCP7940N initialized."));
// }

// /**
// * Conduct any initialization necessary of the EERPOM
// * either internally to Arduino or external in the peripheral
// */
// void setupEEPROM()
// {
//     // Device address is 0x50
// }

// /**
//  * Data read/write functions
//  */

// /**
//  * Function takes a pointer to an Accel data object
//  * and populates the contents with the X, Y, and Z acceleration values.
//  * Value may be raw readings or normalized relative to 0g.
//  */
// void readAcceleration(Accel *data)
// {
//     adxl.readAccel(&data->x, &data->y, &data->z);
// }

// /**
//  * Function takes a pointer to a DateTime object and
//  * populates with the current DateTime in MM/DD/YYYY HH:MM:SS
//  * format. Return values must be human readable
//  */
// void readDateTime(DateTime *data)
// {
//     *data = rtc.now();
// }

// /**
//  * Function writes a series of uint16_t values to the EEPROM
//  * from the data array. Length of array is specified by the len parameter.
//  * All writing is assumed to occur at EEPROM storage address 0x0.
//  * Any existing data should be overwritten.
//  */
// void writeDataToEEPROM(uint8_t *data, uint8_t len)
// {
//     uint16_t dataAddress = 0x0;
//     uint16_t deviceAddress = 0x50;

//     Wire.beginTransmission((uint8_t)deviceAddress); // initiate transaction

//     Wire.write((uint8_t)(dataAddress >> 8));   // First half of 16 - bit address
//     Wire.write((uint8_t)(dataAddress & 0xFF)); // second half

//     for (int i = 0; i < len; i++)
//     {
//         // Per datasheet, successive write operations are sequential in memory
//         Wire.write((uint8_t)data[i]);
//     }

//     Wire.endTransmission(); // Nothing's wrong it's fine
//     delay(5);               // Allow time for write to occur - write should not be followed immediately by a read
// }

// /**
//  * Function reads a sequence of uint16_t values from the EEPROM
//  * and stores the result in the buffer array. Length of buffer is
//  * specified by the len parameter. All reads are assumed to begin at EEPROM storage
//  * address 0x0.
//  */
// void readDataFromEEPROM(uint8_t *buffer, uint16_t len)
// {
//     uint16_t dataAddress = 0x0;
//     uint16_t deviceAddress = 0x50;

//     Wire.beginTransmission((uint8_t)deviceAddress); // initiate transaction

//     Wire.write((uint8_t)(dataAddress >> 8));   // First half of 16 - bit address
//     Wire.write((uint8_t)(dataAddress & 0xFF)); // second half

//     Wire.endTransmission();

//     for (int i = 0; i < len; i++)
//     {
//         Wire.requestFrom((uint8_t)0x50, (uint8_t)1);
//         if (Wire.available())
//         {
//             buffer[i] = Wire.read();
//         }
//     }
// }

// /**
//   * typical sample code for your milestone. Particular
//   * implementations may be different if you are in a different
//   * development environment
//   */
// void setup()
// {
//     Serial.begin(9600);
//     while (!Serial)
//     {
//         ;
//     }

//     /*
//    * Configure all buses
//    */
//     setupI2C();
//     setupSPI();

//     /**
//      * Initialize the EEPROMnce of one bus line in pF.
//     2: As a transmitter, the device must provide an internal minimum delay time to bridge the undefined region (minimum
//     300 ns) of the falling edge of SCL to avoid unintended generation of Start or Stop conditions.
//     3: The combined TSP and VHYS specifications are due to new Schmitt Trigger inputs which provide improved noise spike
//     suppression. This eliminates the need for
//      */
//     setupEEPROM();

//     /**
//    * Configure the ADXL34nce of one bus line in pF.
// 2: As a transmitter, the device must provide an internal minimum delay time to bridge the undefined region (minimum
// 300 ns) of the falling edge of SCL to avoid unintended generation of Start or Stop conditions.
// 3: The combined TSP and VHYS specifications are due to new Schmitt Trigger inputs which provide improved noise spike
// suppression. This eliminates the need for
//    */
//     setupADXL345();

//     setupRTC();
// }

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


// // /******************************************************************************
// //  * MicroOLED_Demo.ino
// //  * SFE_MicroOLED Library Demo
// //  * Jim Lindblom @ SparkFun Electronics
// //  * Original Creation Date: October 27, 2014
// //  * 
// //  * This sketch uses the MicroOLED library to draw a 3-D projected
// //  * cube, and rotate it along all three axes.
// //  * 
// //  * Development environment specifics:
// //  *  Arduino 1.0.5
// //  *  Arduino Pro 3.3V
// //  *  Micro OLED Breakout v1.0
// //  * 
// //  * This code is beerware; if you see me (or any other SparkFun employee) at the
// //  * local, and you've found our code helpful, please buy us a round!
// //  * 
// //  * Distributed as-is; no warranty is given.
// //  ******************************************************************************/
// // #include <Wire.h>  // Include Wire if you're using I2C
// // // #include <SPI.h>  // Include SPI if you're using SPI
// // #include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library

// // //////////////////////////
// // // MicroOLED Definition //
// // //////////////////////////
// // #define PIN_RESET 9  // Connect RST to pin 9
// // #define PIN_DC    1  // Connect DC to pin 8
// // //////////////////////////////////
// // // MicroOLED Object Declaration //
// // //////////////////////////////////
// // /**
// //  * Important
// //  * Set address (PIN_DC)  = 1 and not 0
// //  */
// // MicroOLED oled(PIN_RESET, PIN_DC);    // I2C declaration


// // void setup()
// // {
// //   oled.begin();    // Initialize the OLED
// //   oled.clear(ALL); // Clear the display's internal memory
// //   oled.display();  // Display what's in the buffer (splashscreen)
// //   delay(1000);     // Delay 1000 ms
// //   oled.clear(PAGE); // Clear the buffer.
  
// //   randomSeed(analogRead(A0) + analogRead(A1));
// // }


// // // Center and print a small title
// // // This function is quick and dirty. Only works for titles one
// // // line long.
// // void printTitle(String title, int font)
// // {
// //   int middleX = oled.getLCDWidth() / 2;
// //   int middleY = oled.getLCDHeight() / 2;
  
// //   oled.clear(PAGE);
// //   oled.setFontType(font);
// //   // Try to set the cursor in the middle of the screen
// //   oled.setCursor(middleX - (oled.getFontWidth() * (title.length()/2)),
// //                  middleY - (oled.getFontWidth() / 2));
// //   // Print the title:
// //   oled.print(title);
// //   oled.display();
// //   delay(1500);
// //   oled.clear(PAGE);
// // }


// // void pixelExample()
// // {
// //   printTitle("Pixels", 1);
  
// //   for (int i=0; i<512; i++)
// //   {
// //     oled.pixel(random(oled.getLCDWidth()), random(oled.getLCDHeight()));
// //     oled.display();
// //   }
// // }

// // void lineExample()
// // {
// //   int middleX = oled.getLCDWidth() / 2;
// //   int middleY = oled.getLCDHeight() / 2;
// //   int xEnd, yEnd;
// //   int lineWidth = min(middleX, middleY);
  
// //   printTitle("Lines!", 1);
  
// //   for (int i=0; i<3; i++)
// //   {
// //     for (int deg=0; deg<360; deg+=15)
// //     {
// //       xEnd = lineWidth * cos(deg * PI / 180.0);
// //       yEnd = lineWidth * sin(deg * PI / 180.0);
      
// //       oled.line(middleX, middleY, middleX + xEnd, middleY + yEnd);
// //       oled.display();
// //       delay(10);
// //     }
// //     for (int deg=0; deg<360; deg+=15)
// //     {
// //       xEnd = lineWidth * cos(deg * PI / 180.0);
// //       yEnd = lineWidth * sin(deg * PI / 180.0);
      
// //       oled.line(middleX, middleY, middleX + xEnd, middleY + yEnd, BLACK, NORM);
// //       oled.display();
// //       delay(10);
// //     }
// //   }
// // }

// // void shapeExample()
// // {
// //   printTitle("Shapes!", 0);
  
// //   // Silly pong demo. It takes a lot of work to fake pong...
// //   int paddleW = 3;  // Paddle width
// //   int paddleH = 15;  // Paddle height
// //   // Paddle 0 (left) position coordinates
// //   int paddle0_Y = (oled.getLCDHeight() / 2) - (paddleH / 2);
// //   int paddle0_X = 2;
// //   // Paddle 1 (right) position coordinates
// //   int paddle1_Y = (oled.getLCDHeight() / 2) - (paddleH / 2);
// //   int paddle1_X = oled.getLCDWidth() - 3 - paddleW;
// //   int ball_rad = 2;  // Ball radius
// //   // Ball position coordinates
// //   int ball_X = paddle0_X + paddleW + ball_rad;
// //   int ball_Y = random(1 + ball_rad, oled.getLCDHeight() - ball_rad);//paddle0_Y + ball_rad;
// //   int ballVelocityX = 1;  // Ball left/right velocity
// //   int ballVelocityY = 1;  // Ball up/down velocity
// //   int paddle0Velocity = -1;  // Paddle 0 velocity
// //   int paddle1Velocity = 1;  // Paddle 1 velocity
    
// //   //while(ball_X >= paddle0_X + paddleW - 1)
// //   while ((ball_X - ball_rad > 1) && 
// //          (ball_X + ball_rad < oled.getLCDWidth() - 2))
// //   {
// //     // Increment ball's position
// //     ball_X+=ballVelocityX;
// //     ball_Y+=ballVelocityY;
// //     // Check if the ball is colliding with the left paddle
// //     if (ball_X - ball_rad < paddle0_X + paddleW)
// //     {
// //       // Check if ball is within paddle's height
// //       if ((ball_Y > paddle0_Y) && (ball_Y < paddle0_Y + paddleH))
// //       {
// //         ball_X++;  // Move ball over one to the right
// //         ballVelocityX = -ballVelocityX; // Change velocity
// //       }
// //     }
// //     // Check if the ball hit the right paddle
// //     if (ball_X + ball_rad > paddle1_X)
// //     {
// //       // Check if ball is within paddle's height
// //       if ((ball_Y > paddle1_Y) && (ball_Y < paddle1_Y + paddleH))
// //       {
// //         ball_X--;  // Move ball over one to the left
// //         ballVelocityX = -ballVelocityX; // change velocity
// //       }
// //     }
// //     // Check if the ball hit the top or bottom
// //     if ((ball_Y <= ball_rad) || (ball_Y >= (oled.getLCDHeight() - ball_rad - 1)))
// //     {
// //       // Change up/down velocity direction
// //       ballVelocityY = -ballVelocityY;
// //     }
// //     // Move the paddles up and down
// //     paddle0_Y += paddle0Velocity;
// //     paddle1_Y += paddle1Velocity;
// //     // Change paddle 0's direction if it hit top/bottom
// //     if ((paddle0_Y <= 1) || (paddle0_Y > oled.getLCDHeight() - 2 - paddleH))
// //     {
// //       paddle0Velocity = -paddle0Velocity;
// //     }
// //     // Change paddle 1's direction if it hit top/bottom
// //     if ((paddle1_Y <= 1) || (paddle1_Y > oled.getLCDHeight() - 2 - paddleH))
// //     {
// //       paddle1Velocity = -paddle1Velocity;
// //     }
    
// //     // Draw the Pong Field
// //     oled.clear(PAGE);  // Clear the page
// //     // Draw an outline of the screen:
// //     oled.rect(0, 0, oled.getLCDWidth() - 1, oled.getLCDHeight());
// //     // Draw the center line
// //     oled.rectFill(oled.getLCDWidth()/2 - 1, 0, 2, oled.getLCDHeight());
// //     // Draw the Paddles:
// //     oled.rectFill(paddle0_X, paddle0_Y, paddleW, paddleH);
// //     oled.rectFill(paddle1_X, paddle1_Y, paddleW, paddleH);
// //     // Draw the ball:
// //     oled.circle(ball_X, ball_Y, ball_rad);
// //     // Actually draw everything on the screen:
// //     oled.display();
// //     delay(25);  // Delay for visibility
// //   }
// //   delay(1000);
// // }

// // void textExamples()
// // {
// //   printTitle("Text!", 1);
  
// //   // Demonstrate font 0. 5x8 font
// //   oled.clear(PAGE);     // Clear the screen
// //   oled.setFontType(0);  // Set font to type 0
// //   oled.setCursor(0, 0); // Set cursor to top-left
// //   // There are 255 possible characters in the font 0 type.
// //   // Lets run through all of them and print them out!
// //   for (int i=0; i<=255; i++)
// //   {
// //     // You can write byte values and they'll be mapped to
// //     // their ASCII equivalent character.
// //     oled.write(i);  // Write a byte out as a character
// //     oled.display(); // Draw on the screen
// //     delay(10);      // Wait 10ms
// //     // We can only display 60 font 0 characters at a time.
// //     // Every 60 characters, pause for a moment. Then clear
// //     // the page and start over.
// //     if ((i%60 == 0) && (i != 0))
// //     {
// //       delay(500);           // Delay 500 ms
// //       oled.clear(PAGE);     // Clear the page
// //       oled.setCursor(0, 0); // Set cursor to top-left
// //     }
// //   }
// //   delay(500);  // Wait 500ms before next example
  
// //   // Demonstrate font 1. 8x16. Let's use the print function
// //   // to display every character defined in this font.
// //   oled.setFontType(1);  // Set font to type 1
// //   oled.clear(PAGE);     // Clear the page
// //   oled.setCursor(0, 0); // Set cursor to top-left
// //   // Print can be used to print a string to the screen:
// //   oled.print(" !\"#$%&'()*+,-./01234");
// //   oled.display();       // Refresh the display
// //   delay(1000);          // Delay a second and repeat
// //   oled.clear(PAGE);
// //   oled.setCursor(0, 0);
// //   oled.print("56789:;<=>?@ABCDEFGHI");
// //   oled.display();
// //   delay(1000);
// //   oled.clear(PAGE);
// //   oled.setCursor(0, 0);
// //   oled.print("JKLMNOPQRSTUVWXYZ[\\]^");
// //   oled.display();
// //   delay(1000);
// //   oled.clear(PAGE);
// //   oled.setCursor(0, 0);
// //   oled.print("_`abcdefghijklmnopqrs");
// //   oled.display();
// //   delay(1000);
// //   oled.clear(PAGE);
// //   oled.setCursor(0, 0);
// //   oled.print("tuvwxyz{|}~");
// //   oled.display();
// //   delay(1000);
  
// //   // Demonstrate font 2. 10x16. Only numbers and '.' are defined. 
// //   // This font looks like 7-segment displays.
// //   // Lets use this big-ish font to display readings from the
// //   // analog pins.
// //   for (int i=0; i<25; i++)
// //   {
// //     oled.clear(PAGE);            // Clear the display
// //     oled.setCursor(0, 0);        // Set cursor to top-left
// //     oled.setFontType(0);         // Smallest font
// //     oled.print("A0: ");          // Print "A0"
// //     oled.setFontType(2);         // 7-segment font
// //     oled.print(analogRead(A0));  // Print a0 reading
// //     oled.setCursor(0, 16);       // Set cursor to top-middle-left
// //     oled.setFontType(0);         // Repeat
// //     oled.print("A1: ");
// //     oled.setFontType(2);
// //     oled.print(analogRead(A1));
// //     oled.setCursor(0, 32);
// //     oled.setFontType(0);
// //     oled.print("A2: ");
// //     oled.setFontType(2);
// //     oled.print(analogRead(A2));
// //     oled.display();
// //     delay(100);
// //   }
  
// //   // Demonstrate font 3. 12x48. Stopwatch demo.
// //   oled.setFontType(3);  // Use the biggest font
// //   int ms = 0;
// //   int s = 0;
// //   while (s <= 5)
// //   {
// //     oled.clear(PAGE);     // Clear the display
// //     oled.setCursor(0, 0); // Set cursor to top-left
// //     if (s < 10)
// //       oled.print("00");   // Print "00" if s is 1 digit
// //     else if (s < 100)     
// //       oled.print("0");    // Print "0" if s is 2 digits
// //     oled.print(s);        // Print s's value
// //     oled.print(":");      // Print ":"
// //     oled.print(ms);       // Print ms value
// //     oled.display();       // Draw on the screen
// //     ms++;         // Increment ms
// //     if (ms >= 10) // If ms is >= 10
// //     {
// //       ms = 0;     // Set ms back to 0
// //       s++;        // and increment s
// //     }
// //   }
  
// //   // Demonstrate font 4. 31x48. Let's use the print function
// //   // to display some characters defined in this font.
// //   oled.setFontType(4);  // Set font to type 4
// //   oled.clear(PAGE);     // Clear the page
// //   oled.setCursor(0, 0); // Set cursor to top-left
// //   // Print can be used to print a string to the screen:
// //   oled.print("OL");
// //   oled.display();       // Refresh the display
// //   delay(1000);          // Delay a second and repeat
// //   oled.clear(PAGE);
// //   oled.setCursor(0, 0);
// //   oled.print("ED");
// //   oled.display();
// //   delay(1000);
// // }

// // void loop()
// // {
// //   pixelExample();  // Run the pixel example function
// //   lineExample();   // Then the line example function
// //   shapeExample();  // Then the shape example
// //   textExamples();  // Finally the text example
// // }

