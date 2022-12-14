#define coinSlot 6
int pulse;
int coinSlotStatus;
void setup() {
  // put your setup code here, to run once:
  pinMode(coinSlot, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  coinSlotStatus = digitalRead(coinSlot);
  delay(35);
  if(coinSlotStatus == 0){
    pulse+=1;    
    Serial.println(pulse);
    }
    delay(35);
}
