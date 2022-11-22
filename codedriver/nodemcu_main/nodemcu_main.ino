#include<SoftwareSerial.h>
SoftwareSerial srlKeypad (D1,D2); //Rx Tx (connect Tx of the arduino nano to D1 nodemcu)
void setup() {
  Serial.begin(115200);
  srlKeypad.begin(9600);

}

void loop() {
  String fet = srlKeypad.readString();
  Serial.println(fet);
  delay(50);
}
