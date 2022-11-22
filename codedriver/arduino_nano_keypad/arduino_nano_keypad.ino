 /*
  3X4-MPR121-Capacitive-Touch-Keypad-Module
  Modified on 10 Jan 2021
  by Amir Mohammad Shojaee @ Electropeak
  Home
  
  based on Adafruit Library Example 
*/

#include <Wire.h>
#include "Adafruit_MPR121.h"
#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif
//#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows


// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
void setup() {
//  lcd.init(); // initialize the lcd
//  lcd.backlight();
//  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
//  lcd.print("Arduino");        // print message at (0, 0)
//  lcd.setCursor(2, 1);         // move cursor to   (2, 1)
//  lcd.print("GetStarted.com"); // print message at (2, 1)
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    //Serial.println("KEYPAD ERROR");
    while (1);
  }
  //Serial.println("KEYPAD OKAY");
}

void loop() {
  // Get the currently touched pads
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
        Serial.println(i);
    }
//    // if it *was* touched and now *isnt*, alert!
//    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
//        
//      
//    }
  }
  // reset our state
  //lasttouched = currtouched;

  // comment out this line for detailed data from the sensor!
  //return;
  // debugging info, what
  //Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  //Serial.print("Filt: ");
  //for (uint8_t i=0; i<12; i++) {
    //Serial.print(cap.filteredData(i)); Serial.print("\t");
  //}
  //Serial.println();
  //Serial.print("Base: ");
  //for (uint8_t i=0; i<12; i++) {
    //Serial.print(cap.baselineData(i)); Serial.print("\t");
  //}
  //Serial.println();
  
  // put a delay so it isn't overwhelming
  delay(100);
}
