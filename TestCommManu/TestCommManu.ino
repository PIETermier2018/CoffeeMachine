
int DoseCafeState ;

void setup() {
  Serial.begin(9600) ;
  pinMode(23, INPUT) ;
}

void loop() {
  DoseCafeState = digitalRead(23) ;
  Serial.print("DoseCafeState : ") ;
  Serial.println(DoseCafeState) ;
}
