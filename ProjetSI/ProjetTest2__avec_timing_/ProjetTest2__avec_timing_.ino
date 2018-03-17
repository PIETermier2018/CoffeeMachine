//gestion des broches : 
const int cafe = 8 ; //broche module café
const int lait = 9 ; //broche module lait
const int sucre = 10 ; //broche module sucre
const int swcafe = 2 ; //broche sélection menu café
const int swcafelait = 3 ; //broche sélection menu café + lait
const int swcafesucre = 4 ; //broche sélection menu café + sucre

//gérer la sélection des menus : 
int mencafe ; //pour sélectioner un menu
int mencafelait ; //pour sélectioner un menu
int mencafesucre ; //pour sélectioner un menu
int etatcafe ; //état du module café
int etatlait ; //état du module lait
int etatsucre ; //état du module sucre
int etatmen = 0 ; //false si un menu est lancé, true si aucun menu n'est lancé

//gérer le temps : 
const int delaycafe = 2000 ; //timer pour le café
const int delaylait = 2000 ; //timer pour le lait
const int delaysucre = 1000 ; //timer pour le sucre
long tO ;

void setup() {
  Serial.begin(9600) ;
  
  pinMode(cafe, OUTPUT) ;
  pinMode(lait, OUTPUT) ;
  pinMode(sucre, OUTPUT) ;

  digitalWrite(cafe, LOW) ; //passer à 0 café par sécurité
  digitalWrite(lait, LOW) ; //passer à 0 café par sécurité
  digitalWrite(sucre, LOW) ; //passer à 0 café par sécurité
  etatcafe = 0 ;
  etatlait = 0 ;
  etatsucre = 0 ;

  pinMode(swcafe, INPUT) ;
  pinMode(swcafelait, INPUT) ;
  pinMode(swcafesucre, INPUT) ;
}

void loop() {
  Serial.print("etatmen : ") ;
  Serial.print(etatmen) ;
  Serial.print(", tO : ") ;
  Serial.println(tO) ;
  if(etatmen == 0){
    tO = millis() ;
  }
  if((digitalRead(swcafe) || digitalRead(swcafelait) || digitalRead(swcafesucre)) == 1){ //détection d'une sélection d'un menu et verrouillage du menu

    mencafe = digitalRead(swcafe) ;
    mencafelait = digitalRead(swcafelait) ;
    mencafesucre = digitalRead(swcafesucre) ;

    if(millis() - tO <= delaycafe && etatmen == 0){
      digitalWrite(cafe, HIGH) ;
      etatcafe = 1 ;
    }
    
    if(digitalRead(swcafelait) == 1 && millis() - tO <= delaylait && etatmen == 0){
      digitalWrite(lait, HIGH) ;
      etatlait = 1 ;
    }
    
    if(digitalRead(swcafesucre) == 1 && millis() - tO <= delaysucre && etatmen == 0){
      digitalWrite(sucre, HIGH) ;
      etatsucre = 1 ;
    }
    etatmen = 1 ;
  }

  if(millis() - tO > delaycafe){ //arréter le module café
    digitalWrite(cafe, LOW) ;
    etatcafe = 0 ;
  }
  if(millis() - tO > delaylait){ //arréter le module lait
    digitalWrite(lait, LOW) ;
    etatlait = 0 ;
  }
  if(millis() - tO > delaysucre){ //arréter le module sucre
    digitalWrite(sucre, LOW) ;
    etatsucre = 0 ;
  }

  if((mencafe == 1 && etatcafe == 0) || (mencafelait == 1 && etatcafe == 0 && etatlait == 0) || (mencafesucre == 1 && etatcafe == 0 && etatsucre == 0)){
    etatmen = 0 ;
  }
}
