#include <Wire.h>
#include "Adafruit_MPR121.h"
#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

Adafruit_MPR121 cap = Adafruit_MPR121();
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

int count = 0;
int max_digit = 6;
String otp_typed = "";
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Enter your OTP:");
  while (!Serial) { 
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

void keypad_func(){
  currtouched = cap.touched();
  for (uint8_t i=0; i<12; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      
        if(i == 11){
          count = 0;
          otp_typed = "";
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter your OTP:");
          lcd.setCursor(0,1);
          lcd.print(otp_typed);
          
          }
        if(i == 3 && count!=max_digit){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("OTP Error!!");
          lcd.setCursor(0,1);
          lcd.print("Type 6 digit OTP");
          delay(2000);

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter your OTP:");
          lcd.setCursor(0,1);
          lcd.print(otp_typed);
          }

          
        if(i == 3 && count==max_digit){
         
          count = 0;
          otp_typed = "";
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("OTP SENT");
          lcd.setCursor(0,1);
          lcd.print("Loading...");
          delay(2000);

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter your OTP:");
          lcd.setCursor(0,1);
          lcd.print(otp_typed);
        }

        
         if(count<max_digit){
          if(i == 8){
          count+=1;
          otp_typed=otp_typed+"1";

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter your OTP:");
          lcd.setCursor(0,1);
          lcd.print(otp_typed);

          Serial.println(count);
          }
          else if(i == 4){
          count+=1;
          otp_typed=otp_typed+"2";

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter your OTP:");
          lcd.setCursor(0,1);
          lcd.print(otp_typed);

          Serial.println(count);
          }
          else if(i == 0){
          count+=1;
          otp_typed=otp_typed+"3";

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter your OTP:");
          lcd.setCursor(0,1);
          lcd.print(otp_typed);

          Serial.println(count);
          }
          else if(i == 9){
          count+=1;
          otp_typed=otp_typed+"4";

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter your OTP:");
          lcd.setCursor(0,1);
          lcd.print(otp_typed);

          Serial.println(count);
          }
          else if(i == 5){
          count+=1;
          otp_typed=otp_typed+"5";

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter your OTP:");
          lcd.setCursor(0,1);
          lcd.print(otp_typed);

          Serial.println(count);
          }
          else if(i == 1){
          count+=1;
          otp_typed=otp_typed+"6";

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter your OTP:");
          lcd.setCursor(0,1);
          lcd.print(otp_typed);

          Serial.println(count);
          }
          else if(i == 10){
          count+=1;
          otp_typed=otp_typed+"7";

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter your OTP:");
          lcd.setCursor(0,1);
          lcd.print(otp_typed);

          Serial.println(count);
          }
          else if(i == 6){
          count+=1;
          otp_typed=otp_typed+"8";
          
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter your OTP:");
          lcd.setCursor(0,1);
          lcd.print(otp_typed);

          Serial.println(count);
          }
          else if(i == 2){
          count+=1;
          otp_typed=otp_typed+"9";

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter your OTP:");
          lcd.setCursor(0,1);
          lcd.print(otp_typed);
          Serial.println(count);
          }
          
          else if(i == 7){
          count+=1;
          otp_typed=otp_typed+"0";

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter your OTP:");
          lcd.setCursor(0,1);
          lcd.print(otp_typed);
          }
          }
          else{
            
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Press Enter:");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter your OTP:");
          lcd.setCursor(0,1);
          lcd.print(otp_typed);
            
            }
        
        }
       
    }
  delay(100);
  }


void loop() {
  currtouched = cap.touched();
  for (uint8_t i=0; i<12; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      keypad_func();
    }
}
delay(100);
}
