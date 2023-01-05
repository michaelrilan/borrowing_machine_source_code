#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h> 
#include <WiFiClient.h>
const char* ssid     = "RILAN_ZTE_2.4G";
const char* password = "Escanor_7th";
const char* serverName = "http://192.168.1.5/PE_System/physical_education_web_app/machine_API.php";
int IRSensor1 = D4; // connect ir sensor to arduino pin 2
int IRSensor2 = D5;
void setup() 
{
  Serial.begin(115200);
  pinMode (IRSensor1, INPUT); // sensor pin INPUT
  pinMode (IRSensor2, INPUT);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting...");
    delay(500);
    
  }
  if(WiFi.status()== WL_CONNECTED){
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
    }
}

void res_otp(){
  WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "confirmreturn";           
      // Send HTTP POST request
     int httpResponseCode = http.POST(httpRequestData);
     String payloadGet = http.getString();

      // Free resources
      http.end();
      delay(5000);
  }
void loop()
{
  int statusSensor1 = digitalRead (IRSensor1);
  int statusSensor2 = digitalRead (IRSensor2);
  
  if (statusSensor1 == LOW or statusSensor2 == LOW){
    res_otp();
  }
  else
  {
    Serial.println("HIGH siya"); // LED High
  }
  delay(200);
}
