#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial ArduinoSerial (10,11);// daclaring pins 10 and 11 as RX/TX pins of nano
String dataIn;
char c;
int rec_ir_signal = 0;
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

int count = 0;
int max_digit = 6;
String otp_typed = "";

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows
const byte ROWS = 4; // Define the number of rows on the keypad
const byte COLS = 3; // Define the number of columns on the keypad
char keys[ROWS][COLS] = { // Matrix defining character to return for each key
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pins (R0-R3) of the keypad
byte colPins[COLS] = {4, 3, 2}; //connect to the column pins (C0-C2) of the keypad
//initialize an instance of class
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(115200);
  ArduinoSerial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Enter your OTP:");
}

void loop(){
  char key = keypad.getKey();
  if (key){     // If key is pressed, send it to the Serial Monitor Window
    Serial.println(key);
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print(key);
  if(key == '*'){
     count = 0;
     otp_typed = "";
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Enter your OTP:");
     lcd.setCursor(0,1);
     lcd.print(otp_typed);
    }
  if(key == '#' && count!=max_digit){
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
     delay(20000);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Enter Your OTP:");
     lcd.setCursor(0,1);
     lcd.print(otp_typed); 
    }
  if(count<max_digit && key != '#' && key != '*'){
    count+=1;
    otp_typed=otp_typed+key;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter your OTP:");
    lcd.setCursor(0,1);
    lcd.print(otp_typed);
    Serial.println(count);
    }
   else if(count<max_digit && key == '#'){  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Press Enter:");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter your OTP:");
    lcd.setCursor(0,1);
    lcd.print(otp_typed);
    Serial.println("press enter");
            
     }
  }
}
 
