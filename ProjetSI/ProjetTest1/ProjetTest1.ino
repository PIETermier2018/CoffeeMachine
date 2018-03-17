int cafe = 8 ; //broche module café
int lait = 9 ; //broche module lait
int sucre = 10 ; //broche module sucre
int swcafe = 2 ; //broche sélection menu café
int swcafelait = 3 ; //broche sélection menu café + lait
int swcafesucre = 4 ; //broche sélection menu café + sucre

int mencafe ; //pour le port série
int mencafelait ; //pour le port série
int mencafesucre ; //pour le port série

void setup() {
  pinMode(cafe, OUTPUT) ;
  pinMode(lait, OUTPUT) ;
  pinMode(sucre, OUTPUT) ;
  
  pinMode(swcafe, INPUT) ;
  pinMode(swcafelait, INPUT) ;
  pinMode(swcafesucre, INPUT) ;
}

void loop() {
  if((digitalRead(swcafe) || digitalRead(swcafelait) || digitalRead(swcafesucre)) == 1){ //détection d'une sélection d'un menu
      digitalWrite(cafe, HIGH) ;
    if(digitalRead(swcafelait) == 1){
      digitalWrite(lait, HIGH) ;
    }
    
    if(digitalRead(swcafesucre) == 1){
      digitalWrite(sucre, HIGH) ;
    }
  }
  else{
    digitalWrite(cafe, LOW) ;
    digitalWrite(lait, LOW) ;
    digitalWrite(sucre, LOW) ;
  }
}
