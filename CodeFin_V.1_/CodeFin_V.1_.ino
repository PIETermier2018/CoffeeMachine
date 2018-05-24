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
int lance = 34 ;
int pret = 35 ;

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

  DosesCafeRe[0] = 100 ;
  DosesCafeRe[1] = 200 ;
  DosesCafeRe[2] = 300 ;

  DosesSucreRe[0] = 0 ;
  DosesSucreRe[1] = 100 ;
  DosesSucreRe[2] = 200 ;
  DosesSucreRe[3] = 300 ;

  //Setup LED de selection :
  for (i=22; i<=35 ; i++) {
    pinMode(i, OUTPUT) ;
  }
  digitalWrite(posLEDEau, HIGH) ;
  digitalWrite(posLEDCafe, HIGH) ;
  digitalWrite(posLEDSucre, HIGH) ;
  digitalWrite(pret, HIGH) ;

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

void LancementComm(int Eau, int Cafe, int Sucre){//fonction de lancement d'une commande  
  //Stats :
  digitalWrite(34, LOW) ;
  digitalWrite(35, HIGH) ;
  Serial.println("Lancement Commande...") ;
  Serial.print("- Temps pour ecoulement entre electrovannes : ") ;
  Serial.print(TempsEc[Eau-1]) ;
  Serial.print("- Nombre de doses d'eau : ") ;
  Serial.print(StateCommG[0]) ;
  Serial.print(" , temps de chauffe de : ") ;
  Serial.println(TempsChauff[Eau-1]) ;
  Serial.print("- Nombre de doses de cafe : ") ;
  Serial.print(StateCommG[1]) ;
  Serial.print(" , nombre de pas : ") ;
  Serial.println(DosesCafeRe[Cafe-1]) ;
  Serial.print("- Nombre de doses de sucre : ") ;
  Serial.print(StateCommG[2]) ;
  Serial.print(" , nombre de pas : ") ;
  Serial.println(DosesSucreRe[Sucre]) ;

/*  //Commandes :
    //Verser eau :
  digitalWrite(electroV2, LOW) ;
  digitalWrite(electroV1, HIGH) ;
  delay(TempsEc[Eau-1]) ;

    //Chauffer Eau :
  digitalWrite(electroV1, LOW) ;
  digitalWrite(resChauff, HIGH) ;
  delay(TempsChauff[Eau-1]) ;*/


}

/*void ModStateBlue(int State){//fonction de changement des states de doses de la commande bluetooth
  Serial.println("Valeur bluetooth") ;
  }*/

void loop() {
  butState[0] = digitalRead(Eaubut) ;
  butState[1] = digitalRead(Cafebut) ;
  butState[2] = digitalRead(Sucrebut) ;
  confirmation = digitalRead(Confirmationbut) ;
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
    LancementComm(StateCommG[0], StateCommG[1], StateCommG[2]) ;
/*      //Distribuer poudre et verser Eau :
    Cafe.step(DosesCafeRe[(StateCommG[1])-1], FORWARD, DOUBLE) ;
    Cafe.release() ;
    Sucre.step(DosesSucreRe[StateCommG[2]], FORWARD, DOUBLE) ;
    Sucre.release() ;

    digitalWrite(electroV2, HIGH) ;
    delay(TempsEc[(StateCommG[0])-1]) ;
    digitalWrite(electroV1, LOW) ;*/

    digitalWrite(34, HIGH) ;
    digitalWrite(35, LOW) ;
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
