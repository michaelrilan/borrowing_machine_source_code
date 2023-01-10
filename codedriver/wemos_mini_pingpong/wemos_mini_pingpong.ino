#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h> 
#include <WiFiClient.h>
const char* ssid     ="RILAN_ZTE_2.4G";
const char* password = "Escanor_7th";
const char* serverName = "http://www.physicaleducationsystem.online/machine_API_return.php";
int IRSensor1 = D6; // connect ir sensor to arduino pin 4
void setup() 
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode (IRSensor1, INPUT); // sensor pin INPUT
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting...");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
  if(WiFi.status()== WL_CONNECTED){
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
    }
  else{
    digitalWrite(LED_BUILTIN, HIGH);
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
      delay(1000);
  }
void loop()
{
  int statusSensor1 = digitalRead (IRSensor1);
  
  if (statusSensor1 == LOW){
    Serial.println("LOW siya"); // LED High
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    Serial.println("HIGH siya"); // LED High
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(500);
}
