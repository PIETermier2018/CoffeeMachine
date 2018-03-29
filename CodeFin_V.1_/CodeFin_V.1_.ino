#include <SoftwareSerial.h>
#include <AFMotor.h>

  //init port Serie bluetooth
const int Rx = 23 ;
const int Tx = 22 ;
SoftwareSerial blue(Rx, Tx) ;

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
int blueState ;

 //init states doses café :
int StateCommG[3] ;


//AF_Stepper Cafe(1, 200) ;
//AF_Stepper Sucre(2, 200) ;

void setup() {
  Serial.begin(9600) ;
  blue.begin(9600) ;
  Serial.println("") ;
  Serial.println("Setup...") ;
  StateCommG[0] = 1 ;
  StateCommG[1] = 1 ;
  StateCommG[2] = 0 ;

  for(i=0; i<=3; i++){
      lastButState[i] = 0 ;
  }
  
  pinMode(Eaubut, INPUT) ;
  pinMode(Cafebut, INPUT) ;
  pinMode(Sucrebut, INPUT) ;
  pinMode(Confirmationbut, OUTPUT) ;
  Serial.println("Fin Setup") ;
}

void ModStateComm(int Eau, int Cafe, int Sucre){//fonction de changement des states de doses pour la commande manuelle
  
  if(Eau == 1){
    if(StateCommG[0] < 5)
    StateCommG[0]++ ;
    else
    StateCommG[0] = 1 ;
  }
  if(Cafe == 1){
    if(StateCommG[1] < 3){
      StateCommG[1]++ ;
    }
    else
    StateCommG[1] = 1 ;
  }
  if(Sucre == 1){
    if(StateCommG[2] < 3){
      StateCommG[2]++ ;
    }
    else
    StateCommG[2] = 0 ;
  }
}

void ModStateBlue(int State){//fonction de changement des states de doses de la commande bluetooth
  Serial.println("Valeur bluetooth") ;
}

void loop() {
  butState[0] = digitalRead(Eaubut) ;
  butState[1] = digitalRead(Cafebut) ;
  butState[2] = digitalRead(Sucrebut) ;
  confirmation = digitalRead(Confirmationbut) ;
  blueState = blue.read() ;

  if(blueState != -1){
    ModStateBlue(blueState) ;
  }
  
  if(butState[0] != lastButState[0] || butState[1] != lastButState[1] || butState[2] != lastButState[2]){
    if(butState[0] == HIGH || butState[1] == HIGH || butState[2] == HIGH){
      ModStateComm(butState[0], butState[1], butState[2]) ;
    }
  }

  lastButState[0] = butState[0] ;
  lastButState[1] = butState[1] ;
  lastButState[2] = butState[2] ;


  if(confirmation == HIGH || butState[0] == HIGH || butState[1] == HIGH || butState[2] == HIGH){
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
