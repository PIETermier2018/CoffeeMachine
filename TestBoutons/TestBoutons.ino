const int Confirmation = 50 ;
const int Eaubut = 51 ;
const int Cafebut = 52 ;
const int Sucrebut = 53 ;

int butState[3] ;
int lastButState[3] ;

int i ;

void setup() {
  Serial.begin(9600) ;
  
  lastButState[0] = 0 ;
  lastButState[1] = 0 ;
  lastButState[2] = 0 ;

  pinMode(Confirmation, INPUT) ;
  pinMode(Eaubut, INPUT) ;
  pinMode(Cafebut, INPUT) ;
  pinMode(Sucrebut, INPUT) ;
}

void loop() {
  butState[0] = digitalRead(Eaubut) ;
  butState[1] = digitalRead(Cafebut) ;
  butState[2] = digitalRead(Sucrebut) ;

  if(butState[0] != lastButState[0] || butState[1] != lastButState[1] || butState[2] != lastButState[2] || digitalRead(Confirmation) == HIGH){
    if(butState[0] == HIGH || butState[1] == HIGH || butState[2] == HIGH || digitalRead(Confirmation) == HIGH){
      Serial.println("Appui") ;
    }
  }

/*  if(digitalRead(Confirmation) == HIGH){
    Serial.println("Confirmation") ;
  }*/
  lastButState[0] = butState[0] ;
  lastButState[1] = butState[1] ;
  lastButState[2] = butState[2] ;
}
