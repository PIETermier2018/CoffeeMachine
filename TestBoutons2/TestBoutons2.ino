void setup() {
  Serial.begin(9600) ;
  pinMode(50, INPUT) ;
}

void loop() {
  if(digitalRead(50) == HIGH){
    Serial.println("Bouton : 1") ;
  }
  else
    Serial.println("Bouton : 0") ;
}
