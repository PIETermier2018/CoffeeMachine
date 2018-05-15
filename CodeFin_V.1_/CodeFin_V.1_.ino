//#include <SoftwareSerial.h>
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

AF_Stepper Cafe(1, 200) ;
AF_Stepper Sucre(2, 200) ;


void setup() {
  Serial.begin(9600) ;
  Serial.println("") ;
  Serial.println("Setup...") ;
  
  Cafe.setSpeed(100) ;
  Sucre.setSpeed(100) ;
  
  StateCommG[0] = 1 ;
  StateCommG[1] = 1 ;
  StateCommG[2] = 0 ;
  //Setup temps de chauffe/nombre de pas :
  
  TempsChauff[0] = 251100 ;
  TempsChauff[1] = 502200 ;
  TempsChauff[2] = 753300 ;
  TempsChauff[3] = 1004400 ;
  TempsChauff[4] = 1255500 ;

  DosesCafeRe[0] = 100 ;
  DosesCafeRe[1] = 200 ;
  DosesCafeRe[2] = 300 ;

  DosesSucreRe[0] = 0 ;
  DosesSucreRe[1] = 100 ;
  DosesSucreRe[2] = 200 ;
  DosesSucreRe[3] = 300 ;


  for (i = 22; i <= 24; i++) {
    pinMode(i, OUTPUT) ;
  }

  for (i = 0; i <= 3; i++) {
    lastButState[i] = 0 ;
  }

  pinMode(Eaubut, INPUT) ;
  pinMode(Cafebut, INPUT) ;
  pinMode(Sucrebut, INPUT) ;
  pinMode(Confirmationbut, OUTPUT) ;
  Serial.println("Fin Setup") ;
}

void ModStateComm(int Eau, int Cafe, int Sucre){ //fonction de changement des states de doses pour la commande manuelle

  if (Eau == 1) {
    if (StateCommG[0] < 5)
      StateCommG[0]++ ;
    else
      StateCommG[0] = 1 ;
  }
  if (Cafe == 1) {
    if (StateCommG[1] < 3) {
      StateCommG[1]++ ;
    }
    else
      StateCommG[1] = 1 ;
  }
  if (Sucre == 1) {
    if (StateCommG[2] < 3) {
      StateCommG[2]++ ;
    }
    else
      StateCommG[2] = 0 ;
  }
}

void LancementComm(int Eau, int Cafe, int Sucre){//fonction de lancement d'une commande
  Serial.println("Lancement Commande...") ;
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

  delay(2000) ;
  Serial.println("Cafe pret ! (what else ?)") ;
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
