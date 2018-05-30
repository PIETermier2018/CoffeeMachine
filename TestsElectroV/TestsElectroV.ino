int electroV1 = 36 ;
int electroV2 = 37 ;

void setup() {
  Serial.begin(9600) ;
  pinMode(electroV1, OUTPUT) ;
  pinMode(electroV2, OUTPUT) ;
}

void loop() {
  digitalWrite(electroV1, HIGH) ;
  digitalWrite(electroV2, HIGH) ;
  Serial.println("electroV1 : 1") ;
  Serial.println("electroV2 : 1") ;
  delay(2000) ;
  digitalWrite(electroV1, LOW) ;
  digitalWrite(electroV2, LOW) ;
  Serial.println("electroV1 : 0") ;
  Serial.println("electroV2 : 0") ;
  delay(2000) ;
}
