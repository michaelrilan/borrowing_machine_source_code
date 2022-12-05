#include<SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows




SoftwareSerial wemos (D1,D2);//virtual RX and TX pins

int count = 0;
int max_digit = 6;
String otp_typed = "";

int readyy;
HTTPClient http;
WiFiClient client;


// Replace with your network credentials
const char* ssid =      "RILAN_ZTE_2.4G";
const char* password =  "Escanor_7th";


void setup() {
  Serial.begin(115200);
  wemos.begin(9600);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Connecting..");
    lcd.setCursor(0,1);
    lcd.print("too long?restart");
    readyy = 0;
  }  
  if(WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected! WiFi Name: ");
    Serial.println(ssid);
    Serial.print("Connected! IP address: ");
    Serial.println(WiFi.localIP());
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Ready! Enter OTP");
    readyy = 1;
  }
  else{
    Serial.println("wifi Connection Error");
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("WiFi Error");
    readyy = 0;
    }

}


void loop() {
  String msg = wemos.readStringUntil('\r');
    if(readyy == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("WiFi Error");  
    }
    else{
    otp_typed = otp_typed+msg;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ready! Enter OTP");
    lcd.setCursor(0,1);
    lcd.print(otp_typed);
      }
    
}
  
