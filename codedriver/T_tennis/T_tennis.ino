//Mario's Ideas
//Controlling coin acceptor with Arduino

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 
// variable use to measuer the intervals inbetween impulses
int i=0;
int impulsCount=0;
// Sum of all the coins inseted
int total_amount=0;

void setup() {
 // pinMode(2, INPUT_PULLUP);
 Serial.begin(9600);
 // Interrupt connected to PIN D2 executing IncomingImpuls function when signal goes from HIGH to LOW
 attachInterrupt(0,incomingImpuls, FALLING);
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Price: 10 Pesos");
  lcd.setCursor(0,1);
  lcd.print("Credits: 0/10");

}

void incomingImpuls()
{
  impulsCount=impulsCount+1;
  i=0;
}
void creditsmeth(){
    String str_total_amount = String(total_amount);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Price: 10 Pesos");
    lcd.setCursor(0,1);
    lcd.print("Credits:" + str_total_amount +  "/10");
    }
void loop() {
  i=i+1;
  Serial.print("i=");
  Serial.print(i);
  Serial.print(" Impulses:");
  Serial.print(impulsCount);
  Serial.print(" Total:");
  Serial.println(total_amount);
 
  if (i>=30 and impulsCount==1){
    total_amount=total_amount+1;
    impulsCount=0;
    
    creditsmeth();
  }
   if (i>=30 and impulsCount==5){
    total_amount=total_amount+5;
    impulsCount=0;
    creditsmeth();
  }
   if (i>=30 and impulsCount==10){
    total_amount=total_amount+10;
    impulsCount=0;
    creditsmeth();
  }
}
