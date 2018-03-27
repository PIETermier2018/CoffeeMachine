int posLED = 22 ;

void setup() {
  Serial.begin(9600) ;
  pinMode(22, OUTPUT) ;
  pinMode(23, OUTPUT) ;
  pinMode(24, OUTPUT) ;
}

void loop() {
  digitalWrite(posLED, HIGH) ;
  delay(100) ;
  digitalWrite(posLED, LOW) ;
  posLED++ ;
  if(posLED == 25){
    posLED = 22 ;
  }
}
