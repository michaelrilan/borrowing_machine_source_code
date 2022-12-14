#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 
#include <Servo.h>
#define coinSlot 6
int pulse;
int coinSlotStatus;
int buttonState = 0;
int pos = 0;
Servo myservo;
const int buttonPin = 10; 
int price;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(coinSlot, INPUT_PULLUP);
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Price: 10 Pesos");
  lcd.setCursor(0,1);
  lcd.print("Credits: 0/10");
  pinMode(buttonPin, INPUT);
  myservo.attach(11);
  price = 10;
  myservo.write(0);
}



// for the  credits of the user how much the user inserted in the coin acceptor
void creditsmeth(){
    String str_credits = String(pulse);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Price: 10 Pesos");
    lcd.setCursor(0,1);
    lcd.print("Credits:" + str_credits +  "/10");
    }
void display_errorrr(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Insufficient");
    lcd.setCursor(0,1);
    lcd.print("Credits");
    }


void loop() {
  buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
    if(pulse >= price){
     pulse = pulse-price;
     creditsmeth();
     delay(100);
     for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
  }                     // waits 15ms for the servo to reach the position  
      }
    else{
     display_errorrr();
    delay(2000);
    creditsmeth(); 
    delay(500); 
      }
    
  }
  coinSlotStatus = digitalRead(coinSlot);
  delay(35);
  if(coinSlotStatus == 0){
      pulse+=1; 
      creditsmeth();
      delay(35);
    }     
  } 
