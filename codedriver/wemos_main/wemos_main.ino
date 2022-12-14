#include <ESP8266WiFi.h> 

#include <ESP8266HTTPClient.h> 
#include <WiFiClient.h>
#include <SoftwareSerial.h>


SoftwareSerial WemosSerial (D1,D2);// declaring wemos RX/TX pins;;
const char* ssid     = "RILAN_ZTE_2.4G";
const char* password = "Escanor_7th";

const char* serverName = "http://192.168.1.5/PE_System/physical_education_web_app/machine_API.php";

int green_light_pin = D0;
int bball_expand = D3;
int bball_retract = D4;


String dataIn;
char c;

void RGB_color(int green_light_value)
 {
  analogWrite(green_light_pin, green_light_value);
}


void setup() {
  Serial.begin(115200);
  WemosSerial.begin(9600);
  
  pinMode(green_light_pin, OUTPUT);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    RGB_color(255); // Green
    delay(500);
    RGB_color(0);
    delay(500);
  }
  if(WiFi.status()== WL_CONNECTED){
    RGB_color(255); // Green
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
    }
    else{
      RGB_color(0);
      }

}



void loop() {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      while(WemosSerial.available()>0){
          c = WemosSerial.read();
          if(c == '\n') {break;}    
          else {dataIn+=c;}
        }
        if(c == '\n'){
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
          // Send HTTP POST request
          int httpResponseCode = http.POST(httpRequestData);
          String payloadGet = http.getString();
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          Serial.print(payloadGet);
          payloadGet.trim();
          WemosSerial.print(payloadGet + " \n");
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
    delay(1000);
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
