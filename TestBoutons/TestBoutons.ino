const int Eaubut = 8 ;
const int Cafebut = 9 ;
const int Sucrebut = 10 ;

int butState[3] ;
int lastButState[3] ;

int i ;

void setup() {
  Serial.begin(9600) ;
  
  lastButState[0] = 0 ;
  lastButState[1] = 0 ;
  lastButState[2] = 0 ;
  
  pinMode(Eaubut, INPUT) ;
  pinMode(Cafebut, INPUT) ;
  pinMode(Sucrebut, INPUT) ;
}

void loop() {
  butState[0] = digitalRead(Eaubut) ;
  butState[1] = digitalRead(Cafebut) ;
  butState[2] = digitalRead(Sucrebut) ;

  if(butState[0] != lastButState[0] || butState[1] != lastButState[1] || butState[2] != lastButState[2]){
    if(butState[0] == HIGH || butState[1] == HIGH || butState[2] == HIGH){
      Serial.println("Appui") ;
    }
  }
  lastButState[0] = butState[0] ;
  lastButState[1] = butState[1] ;
  lastButState[2] = butState[2] ;
}
