int posLEDCafe = 22 ;
int CafeBut = 51 ;
int i ;

void setup() {
  Serial.begin(9600) ;
  
  pinMode(CafeBut, INPUT) ;
  
  for(i=22; i<=24; i++){
    pinMode(i, OUTPUT) ;
  }
  digitalWrite(22, HIGH) ;
}

void SwitchCafe(int pos){
  digitalWrite(posLEDCafe, LOW) ;
  if(posLEDCafe <= 24){
    posLEDCafe++ ;
    }
  if(posLEDCafe > 24){
    posLEDCafe = 22 ;
    }
  digitalWrite(posLEDCafe, HIGH) ;
  delay(200) ;
}

void loop() {
  if(digitalRead(CafeBut) == 1){
    SwitchCafe(posLEDCafe) ;
  }
}
