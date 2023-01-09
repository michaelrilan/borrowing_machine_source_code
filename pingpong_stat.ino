#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h> 
#include <WiFiClient.h>
const char* ssid     = "PLDTHOMEFIBR6f138";
const char* password = "PLDTWIFI7kpk5";
const char* serverName = "http://192.168.1.9/physical_education_web_app/machine_API_pingpong.php";
int IRSensor1 = D6; // connect ir sensor to arduino pin 6
void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  pinMode (IRSensor1, INPUT); // sensor pin INPUT
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting...");
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW              
    delay(500);
    
  }
  if(WiFi.status()== WL_CONNECTED){
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW              
    }
}

void emptyy(){
      WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "changestat_empty";           
      // Send HTTP POST request
     int httpResponseCode = http.POST(httpRequestData);
     Serial.println(httpResponseCode);
     String payloadGet = http.getString();

      // Free resources
      http.end();
      delay(3000);
  }
  
void non_emptyy(){
      WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "changestat_non_empty";           
      // Send HTTP POST request
     int httpResponseCode = http.POST(httpRequestData);
     Serial.println(httpResponseCode);
     String payloadGet = http.getString();

      // Free resources
      http.end();
      delay(3000);
  }
void loop()
{
  int statusSensor1 = digitalRead (IRSensor1);
  if (statusSensor1 == LOW){
    non_emptyy();
    digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW              
    Serial.println("LOW");
  }
  else
  {
   emptyy();
   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW              
    Serial.println("HIGH");
  }
}
