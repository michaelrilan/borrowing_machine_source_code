#include <ESP8266WiFi.h> 

#include <ESP8266HTTPClient.h> 
#include <WiFiClient.h>
#include <SoftwareSerial.h>


SoftwareSerial WemosSerial (D1,D2);// declaring wemos RX/TX pins;;
const char* ssid     = "RILAN_ZTE_2.4G";
const char* password = "Escanor_7th";

const char* serverName = "http://192.168.1.5/PE_System/physical_education_web_app/machine_API.php";

//declare all the pins for each components
int red_light_pin= D3;
int green_light_pin = D4;
int vball_expand = D5;
int vball_retract = D6;
int bball_expand = D7;
int bball_retract = D8;

String dataIn;
char c;
int conn = 0;
int can_sense = 0;


void RGB_color(int red_light_value, int green_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
}


void setup() {
  Serial.begin(115200);
  WemosSerial.begin(9600);
  
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(vball_expand, OUTPUT);
  pinMode(vball_retract, OUTPUT);
  pinMode(bball_expand, OUTPUT);
  pinMode(bball_retract, OUTPUT);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    conn =0;
    RGB_color(0, 255); // Green
    delay(500);
    RGB_color(255, 0); // Red
    delay(500);
    
  }
  if(WiFi.status()== WL_CONNECTED){
    conn = 1;
    RGB_color(0, 255); // Green
      Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
    }
  else{
    conn = 0;
    RGB_color(0,255); // Red
    
    }

}

void loop() {
    //Check WiFi connection status
    
      while(WemosSerial.available()>0){
          c = WemosSerial.read();
          if(c == '\n') {break;}    
          else {dataIn+=c;}
        }
        
        if(c == '\n'){
          if(conn == 1){
          Serial.println(dataIn);
          WiFiClient client;
          HTTPClient http;      
          // Your Domain name with URL path or IP address with path
          http.begin(client, serverName);
    
          // Specify content-type header
          http.addHeader("Content-Type", "application/x-www-form-urlencoded");
          // Data to send with HTTP POST
          dataIn.trim();
          String httpRequestData = "otpdata="+dataIn;
          c = 0;
          dataIn = "";
          // Send HTTP POST request
          int httpResponseCode = http.POST(httpRequestData);
          String payloadGet = http.getString();
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          Serial.print(payloadGet);
          payloadGet.trim();
          
          WemosSerial.print(payloadGet + " \n");
          
          if(payloadGet == "BORROWINGbasketball"){
              digitalWrite(bball_expand,HIGH);
              digitalWrite(bball_retract,LOW);
              delay(5000);
              digitalWrite(bball_expand,LOW);
              digitalWrite(bball_retract,HIGH);
              delay(5000);
              digitalWrite(bball_expand,LOW);
              digitalWrite(bball_retract,LOW);
            }
            
         else if(payloadGet == "BORROWINGvolleyball"){
              digitalWrite(vball_expand,HIGH);
              digitalWrite(vball_retract,LOW);
              delay(5000);
              digitalWrite(vball_expand,LOW);
              digitalWrite(vball_retract,HIGH);
              delay(5000);
              digitalWrite(vball_expand,LOW);
              digitalWrite(vball_retract,LOW);
            }
         else if(payloadGet == "RETURNINGvolleyball"){
            can_sense = 1;
            }
         else if(payloadGet == "RETURNINGbasketball"){
            can_sense = 1;
            }
          http.end();
        }
       else if(conn ==0){
        String er = "Wifi Error";
        WemosSerial.print(er + " \n");
        Serial.println("WiFi Error");
    }
    }
    
    

    delay(5000);
}
