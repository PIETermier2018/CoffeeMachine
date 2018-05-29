#include <AFMotor.h>

//init port Serie bluetooth
//const int Rx = 23 ;
//const int Tx = 22 ;
//SoftwareSerial blue(Rx, Tx) ;

//init variables divers :
int i ;
int pressbut = 0 ;

//init variables broches :
int Eaubut = 50 ;
int Cafebut = 51 ;
int Sucrebut = 52 ;
int Confirmationbut = 53 ;
int electroV1 = 36 ;
int electroV2 = 37 ;
int resChauff = 38 ;
int posLEDEau = 22 ;
int posLEDCafe = 27 ;
int posLEDSucre = 30 ;
int lance = 35 ;
int pret = 34 ;

//init variables commandes :
int confirmation = 0 ;

int butState[3] ;
int lastButState[3] ;
//int blueState ;

//init states doses café :
int StateCommG[3] ;
int DosesCafeRe[3] ;
int DosesSucreRe[4] ;
long TempsChauff[5] ;
long TempsEc[5] ;

AF_Stepper Cafe(200, 1) ;
AF_Stepper Sucre(200, 2) ;


void setup() {
  Serial.begin(9600) ;
  Serial.println("") ;
  Serial.println("Setup...") ;
  
  Cafe.setSpeed(100) ;
  Sucre.setSpeed(100) ;
  Cafe.release() ;
  Sucre.release() ;
  
  //Setup sélection dose :
  StateCommG[0] = 1 ;
  StateCommG[1] = 1 ;
  StateCommG[2] = 0 ;
  
  //Setup temps de chauffe/nombre de pas :
  TempsChauff[0] = 251100 ;
  TempsChauff[1] = 502200 ;
  TempsChauff[2] = 753300 ;
  TempsChauff[3] = 1004400 ;
  TempsChauff[4] = 1255500 ;

  TempsEc[0] = 16000 ;
  TempsEc[1] = 32000 ;
  TempsEc[2] = 48000 ;
  TempsEc[3] = 64000 ;
  TempsEc[4] = 80000 ;

  DosesCafeRe[0] = 1000 ;
  DosesCafeRe[1] = 2000 ;
  DosesCafeRe[2] = 3000 ;

  DosesSucreRe[0] = 0 ;
  DosesSucreRe[1] = 1000 ;
  DosesSucreRe[2] = 2000 ;
  DosesSucreRe[3] = 3000 ;

  //Setup LED de selection :
  for (i=22; i<=35 ; i++) {
    pinMode(i, OUTPUT) ;
  }
  digitalWrite(posLEDEau, HIGH) ;
  digitalWrite(posLEDCafe, HIGH) ;
  digitalWrite(posLEDSucre, HIGH) ;
  digitalWrite(pret, HIGH) ;
  digitalWrite(lance, LOW) ;
  digitalWrite(electroV1, LOW) ;
  digitalWrite(electroV2, LOW) ;
  digitalWrite(resChauff, LOW) ;

  for (i = 0; i <= 3; i++) {
    lastButState[i] = 0 ;
  }

  //setup reste :
  pinMode(Eaubut, INPUT) ;
  pinMode(Cafebut, INPUT) ;
  pinMode(Sucrebut, INPUT) ;
  pinMode(Confirmationbut, OUTPUT) ;
  pinMode(electroV1, OUTPUT) ;
  pinMode(electroV2, OUTPUT) ;
  pinMode(resChauff, OUTPUT) ;
  
  Serial.println("Fin Setup") ;
}

void ModStateComm(int Eau, int Cafe, int Sucre){ //fonction de changement des states de doses pour la commande manuelle
  digitalWrite(posLEDEau, LOW) ;
  digitalWrite(posLEDCafe, LOW) ;
  digitalWrite(posLEDSucre, LOW) ;
  
  if (Eau == 1) {
    if (StateCommG[0] < 5)
      StateCommG[0]++ ;
    else
      StateCommG[0] = 1 ;
    posLEDEau++ ;
    if(posLEDEau == 27){
      posLEDEau = 22 ;
    }
  }
    
  if (Cafe == 1) {
    if (StateCommG[1] < 3) {
      StateCommG[1]++ ;
    }
    else
      StateCommG[1] = 1 ;
    posLEDCafe++ ;
    if(posLEDCafe == 30){
      posLEDCafe = 27 ;
    }
  }
  if (Sucre == 1) {
    if (StateCommG[2] < 3) {
      StateCommG[2]++ ;
    }
    else
      StateCommG[2] = 0 ;
    posLEDSucre++ ;
    if(posLEDSucre == 34){
      posLEDSucre = 30 ;
    }
  }
  digitalWrite(posLEDEau, HIGH) ;
  digitalWrite(posLEDCafe, HIGH) ;
  digitalWrite(posLEDSucre, HIGH) ;
}

void LancementComm(){//fonction de lancement d'une commande  
  //Stats :
  digitalWrite(pret, LOW) ;
  digitalWrite(lance, HIGH) ;
  Serial.println("Lancement Commande...") ;
  Serial.print("- Temps pour ecoulement entre electrovannes : ") ;
  Serial.println(TempsEc[(StateCommG[0]-1)]) ;
  Serial.print("- Nombre de doses d'eau : ") ;
  Serial.print(StateCommG[0]) ;
  Serial.print(" , temps de chauffe de : ") ;
  Serial.println(TempsChauff[(StateCommG[0]-1)]) ;
  Serial.print("- Nombre de doses de cafe : ") ;
  Serial.print(StateCommG[1]) ;
  Serial.print(" , nombre de pas : ") ;
  Serial.println(DosesCafeRe[(StateCommG[1]-1)]) ;
  Serial.print("- Nombre de doses de sucre : ") ;
  Serial.print(StateCommG[2]) ;
  Serial.print(" , nombre de pas : ") ;
  Serial.println(DosesSucreRe[StateCommG[2]]) ;
}

/*void ModStateBlue(int State){//fonction de changement des states de doses de la commande bluetooth
  Serial.println("Valeur bluetooth") ;
  }*/

void loop() {
  butState[0] = digitalRead(Eaubut) ;
  butState[1] = digitalRead(Cafebut) ;
  butState[2] = digitalRead(Sucrebut) ;
  confirmation = digitalRead(Confirmationbut) ;

  digitalWrite(pret, HIGH) ;
  digitalWrite(lance, LOW) ;
  //  blueState = blue.read() ;

  /*  if(blueState != -1){
      ModStateBlue(blueState) ;
    }*/

  if (butState[0] != lastButState[0] || butState[1] != lastButState[1] || butState[2] != lastButState[2]) {
    if (butState[0] == HIGH || butState[1] == HIGH || butState[2] == HIGH) {
      ModStateComm(butState[0], butState[1], butState[2]) ;
    }
  }
  if(confirmation == HIGH){
    LancementComm() ;

    //ecoulement + chauffage eau :
    Serial.print("ecoulement de l'eau pour ") ;
    Serial.print(TempsEc[(StateCommG[0]-1)]) ;
    Serial.println(" ms...") ;
    
    digitalWrite(electroV2, LOW) ;
    digitalWrite(electroV1, HIGH) ;
    delay(TempsEc[(StateCommG[0]-1)]) ;
    
    Serial.print("chauffage de l'eau pour ") ;
    Serial.print(TempsChauff[(StateCommG[0]-1)]) ;
    Serial.println(" ms...") ;
    
    digitalWrite(electroV1, LOW) ;
    digitalWrite(resChauff, HIGH) ;
    delay(TempsEc[(StateCommG[0]-1)]) ;
    digitalWrite(resChauff, LOW) ;
    
    Serial.println("Fin chauffage eau") ;
    
    //Commande moteur PP :
    Serial.println("distribution poudres...") ;
    Serial.print("- Cafe, nbr pas : ") ;
    Serial.println(DosesCafeRe[(StateCommG[1]-1)]) ;
    
    Cafe.step(DosesCafeRe[(StateCommG[1]-1)], FORWARD, DOUBLE) ;
    Cafe.release() ;
    
    Serial.println("release cafe") ;
    Serial.print("- Sucre, nrb pas : ") ;
    Serial.println(DosesSucreRe[StateCommG[2]]) ;
    
    Sucre.step(DosesSucreRe[StateCommG[2]], FORWARD, DOUBLE) ;
    Sucre.release() ;
    
    Serial.println("release sucre") ;

    //ecoulement eau :
    Serial.println("distribution eau...") ; 
    digitalWrite(electroV2, HIGH) ;
    
    Serial.println("Cafe pret ! (what else ?)") ;
    delay(2000) ;
  }

  lastButState[0] = butState[0] ;
  lastButState[1] = butState[1] ;
  lastButState[2] = butState[2] ;


  if (confirmation == HIGH || butState[0] == HIGH || butState[1] == HIGH || butState[2] == HIGH) {
    Serial.print("Dose Eau : ") ;
    Serial.print(StateCommG[0]) ;
    Serial.print(" , Dose Cafe : ") ;
    Serial.print(StateCommG[1]) ;
    Serial.print(" , Dose Sucre : ") ;
    Serial.print(StateCommG[2]) ;
    Serial.print(" , confirmation : ") ;
    Serial.println(confirmation) ;
  }
}
