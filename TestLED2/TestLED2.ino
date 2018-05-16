int posLEDEau = 22 ;
int posLEDCafe = 27 ;
int posLEDSucre = 30 ;
int Confirmation = 36 ;
int i ;

void setup() {
  Serial.begin(9600) ;
  Serial.println("Setup LED...") ;
  
  for(i=22; i<=35; i++){
    pinMode(i, OUTPUT) ;
  }
  digitalWrite(22, HIGH) ;
  digitalWrite(27, HIGH) ;
  digitalWrite(30, HIGH) ;
  digitalWrite(36, HIGH) ;

  Serial.println("pret") ;
}

void SwitchCafe(){
  digitalWrite(posLEDEau, LOW) ;
  digitalWrite(posLEDCafe, LOW) ;
  digitalWrite(posLEDSucre, LOW) ;
  
  posLEDEau++ ;
  posLEDCafe++ ;
  posLEDSucre++ ;

  if(posLEDEau == 27){
    posLEDEau = 22 ;
  }
  if(posLEDCafe == 30){
    posLEDCafe = 27 ;
  }
  if(posLEDSucre == 34){
    posLEDSucre = 30 ;
  }

  digitalWrite(posLEDEau, HIGH) ;
  digitalWrite(posLEDCafe, HIGH) ;
                             digitalWrite(posLEDSucre, HIGH) ;
  Serial.print("posLEDEau : ") ;
  Serial.print(posLEDEau) ;
  Serial.print(" , posLEDCafe : ") ;
  Serial.print(posLEDCafe) ;
  Serial.print(" , posLEDSucre : ") ;
  Serial.println(posLEDSucre) ;
}

void loop() {
    SwitchCafe() ;
}
