int electroV1 = 36 ;
int electroV2 = 37 ;

void setup() {
  Serial.begin(9600) ;
  pinMode(electroV1, OUTPUT) ;
  pinMode(electroV2, OUTPUT) ;
}

void loop() {
//  digitalWrite(electroV1, HIGH) ;
  digitalWrite(electroV2, HIGH) ;
  digitalWrite(electroV1, HIGH) ;
  Serial.println("ouvert") ;
}
