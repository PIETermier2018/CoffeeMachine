void setup() {
  Serial.begin(9600) ;
  pinMode(25, OUTPUT) ;
}

void loop() {
  digitalWrite(25, HIGH) ;
  Serial.print("pin 25 : ") ;
  Serial.println(digitalRead(25)) ;
  delay(2000) ;
  digitalWrite(25, LOW) ;
  Serial.print("pin 25 : ") ;
  Serial.println(digitalRead(25)) ;
  delay(2000) ;
}
