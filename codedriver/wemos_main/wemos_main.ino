#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h> 
#include <WiFiClient.h>
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial WemosSerial (D1,D2);// declaring wemos RX/TX pins;
const char* ssid     = "RILAN_ZTE_2.4G";
const char* password = "Escanor_7th";

const char* serverName = "http://192.168.1.5/PE_System/physical_education_web_app/machine_API.php";
//

Servo servo_vball;
Servo servo_bball;
String dataIn;
char c;
int vball_expand = D4;
int vball_retract = D5;
int bball_expand = D6;
int bball_retract = D7;

void RGB_color(int red_light_value,int green_light_value)
 {
  analogWrite(D0, green_light_value);
  analogWrite(D3, red_light_value);
  
}


void setup() {
  Serial.begin(115200);
  WemosSerial.begin(9600);

  //setup component's pin
  pinMode(D0,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(vball_expand,OUTPUT);
  pinMode(vball_retract,OUTPUT);
  pinMode(bball_expand,OUTPUT);
  pinMode(bball_retract,OUTPUT);
  
  

  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    RGB_color(0,255);
    delay(500);
    RGB_color(255,0);
    delay(500);
    
  }
  if(WiFi.status()== WL_CONNECTED){
    RGB_color(0,255);
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
    }
    else{
    RGB_color(255,0);
      }
      
  servo_vball.attach(D9);
  servo_bball.attach(D8);
  servo_vball.write(0);
  servo_bball.write(0);
  digitalWrite(bball_expand,HIGH);
  digitalWrite(bball_retract,HIGH);
  digitalWrite(vball_expand,HIGH);
  digitalWrite(vball_retract,HIGH);
  
}

void res_otp(){
  WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "reset_otp";           
      // Send HTTP POST request
     int httpResponseCode = http.POST(httpRequestData);
     String payloadGet = http.getString();

      // Free resources
      http.end();
  }
void loop() {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      while(WemosSerial.available()>0){
          c = WemosSerial.read();
          if(c == '\n') {break;}    
          else {dataIn+=c;}
        }
        if(c == '\n'){
          // Your Domain name with URL path or IP address with path
          http.begin(client, serverName);
    
          // Specify content-type header
          http.addHeader("Content-Type", "application/x-www-form-urlencoded");
          // Data to send with HTTP POST
          dataIn.trim();
          String httpRequestData = "otpdata="+dataIn;           
          // Send HTTP POST request
          int httpResponseCode = http.POST(httpRequestData);
          String payloadGet = http.getString();
          payloadGet.trim();
          if(payloadGet == "RETURN_V_BALL"){
              RGB_color(0,0);
              servo_vball.write(180);
              delay(15000);
              servo_vball.write(0);
              res_otp();
              RGB_color(0,255);
            }
          else if(payloadGet == "RETURN_B_BALL"){
              RGB_color(0,0);
              servo_bball.write(180);
              delay(15000);
              servo_bball.write(0);
              res_otp();
              RGB_color(0,255);
            }
          else if(payloadGet == "BORROW_B_BALL"){
                RGB_color(0,0);
                
                digitalWrite(bball_expand,HIGH);
                digitalWrite(bball_retract,LOW);
                delay(14500);
                digitalWrite(bball_expand,LOW);
                digitalWrite(bball_retract,HIGH);
                delay(14500);
                digitalWrite(bball_expand,HIGH);
                digitalWrite(bball_retract,HIGH);
                digitalWrite(vball_expand,HIGH);
                digitalWrite(vball_retract,HIGH);
                RGB_color(0,255);
                
            }
          else if(payloadGet == "BORROW_V_BALL"){
                RGB_color(0,0);
                digitalWrite(vball_expand,HIGH);
                digitalWrite(vball_retract,LOW);
                delay(14500);
                digitalWrite(vball_expand,LOW);
                digitalWrite(vball_retract,HIGH);
                delay(14500);
                digitalWrite(bball_expand,HIGH);
                digitalWrite(bball_retract,HIGH);
                digitalWrite(vball_expand,HIGH);
                digitalWrite(vball_retract,HIGH);
                RGB_color(0,255);
                
            }
          else if(payloadGet == "otp_error"){
            RGB_color(255,0);
            delay(5000);
            RGB_color(0,255);
            }
          else{
            RGB_color(255,0);
            delay(5000);
            RGB_color(0,255);
            }
          payloadGet = "";
          
    //      
    //      // Free resources
          http.end();
          c = 0;
          dataIn = "";
        }
    
    }
    else {
      Serial.println("WiFi Error");
    }
    delay(500);
}



//      WiFiClient client;
//      HTTPClient http;
//      
//      // Your Domain name with URL path or IP address with path
//      http.begin(client, serverName);
//
//      // Specify content-type header
//      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
//      // Data to send with HTTP POST
//      String httpRequestData = "command";           
//      // Send HTTP POST request
//      int httpResponseCode = http.POST(httpRequestData);
//     String payloadGet = http.getString();
//      Serial.print("HTTP Response code: ");
//      Serial.println(httpResponseCode);
//      Serial.print(payloadGet);
//      
//      // Free resources
//      http.end();
