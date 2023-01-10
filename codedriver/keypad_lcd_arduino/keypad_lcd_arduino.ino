#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include<stdio.h>
SoftwareSerial ArduinoSerial (10,11);// daclaring pins 10 and 11 as RX/TX pins of nano
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows


const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {4, 5, 6, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 9, 10}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String dataIn;
char c;
int count = 0;
int max_digit = 6;
String otp_typed = "";



void setup(){
  Serial.begin(9600);
  ArduinoSerial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);

  lcd.print("Enter your OTP:");
}
void loop()
{
  
 keypadfunction();
 
}
void keypadfunction()
{
char key = keypad.getKey();
//char key = keypad.getKey();
if (key){
    Serial.println(key);
  }
if(key == '*'){
   count = 0;
   otp_typed = "";
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Enter your OTP:");
   lcd.setCursor(0,1);
   lcd.print(otp_typed);
   Serial.println(otp_typed);
  }
if(key == '#' && count!=max_digit){
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("OTP Error!!");
   lcd.setCursor(0,1);
   lcd.print("Type 6 digit OTP");
   delay(2000);
   Serial.println("6 digit only");

   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Enter your OTP:");
   lcd.setCursor(0,1);
   lcd.print(otp_typed);
   Serial.print("Error");
  }
  
  if(key == '#' && count==max_digit){
      ArduinoSerial.print(otp_typed + " \n");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("OTP SENT");
      lcd.setCursor(0,1);
      lcd.print("LOADING..");
      count = 0;
      otp_typed = "";
      delay(2000);
          
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("VIEW THE PROCESS");
      lcd.setCursor(0,1);
      lcd.print("ON YOUR DEVICE");
      delay(15000);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter Your OTP:");
      lcd.setCursor(0,1);
      lcd.print(otp_typed);
      Serial.println("success");
        }
   if(count<max_digit){
    count+=1;
    otp_typed=otp_typed+key;  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter your OTP:");
    lcd.setCursor(0,1);
    lcd.print(otp_typed);
    Serial.println(otp_typed);
  
  }

//if(key == '#' && count!=max_digit){
//   lcd.clear();
//   lcd.setCursor(0,0);
//   lcd.print("OTP Error!!");
//   lcd.setCursor(0,1);
//   lcd.print("Type 6 digit OTP");
//   delay(2000);
//   Serial.println("6 digit only");
//
//   lcd.clear();
//   lcd.setCursor(0,0);
//   lcd.print("Enter your OTP:");
//   lcd.setCursor(0,1);
//   lcd.print(otp_typed);
//   Serial.print("Error");
//}
//
//if(key == '#' && count==max_digit){
//      ArduinoSerial.print(otp_typed + " \n");
//      lcd.clear();
//      lcd.setCursor(0,0);
//      lcd.print("OTP SENT");
//      lcd.setCursor(0,1);
//      lcd.print("LOADING..");
//      count = 0;
//      otp_typed = "";
//      delay(2000);
//          
//      lcd.clear();
//      lcd.setCursor(0,0);
//      lcd.print("VIEW THE PROCESS");
//      lcd.setCursor(0,1);
//      lcd.print("ON YOUR DEVICE");
//      delay(15000);
//
//      lcd.clear();
//      lcd.setCursor(0,0);
//      lcd.print("Enter Your OTP:");
//      lcd.setCursor(0,1);
//      lcd.print(otp_typed);
//      Serial.println("success");
//        }
//
//if(count<max_digit){
//  count+=1;
//  otp_typed=otp_typed+key;  
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Enter your OTP:");
//  lcd.setCursor(0,1);
//  lcd.print(otp_typed);
//  Serial.println(count);
//  Serial.println(otp_typed);
//  
//  }
//else{  
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Press Enter:");
//  delay(1000);
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Enter your OTP:");
//  lcd.setCursor(0,1);
//  lcd.print(otp_typed);
//  Serial.println("press enter");
//   }
}
