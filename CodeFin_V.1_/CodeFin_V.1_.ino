#include <SoftwareSerial.h>
#include <AFMotor.h>

  //init port Serie bluetooth
//int Rx = 52 ;
//int Tx = 53 ;
//SoftwareSerial blue(Rx, Tx) ;

  //init variables divers : 
int i ;
int pressbut = 0 ;

  //init variables broches : 
int Eaubut = 8 ;
int Cafebut = 9 ;
int Sucrebut = 10 ;
int Confirmationbut = 11 ;

  //init variables commandes :
int confirmation = 0 ;
int butState[3] ;
int lastButState[3] ;

 //init states doses café :
int StateCommG[3] ;


//AF_Stepper Cafe(1, 200) ;
//AF_Stepper Sucre(2, 200) ;

void setup() {
  Serial.begin(9600) ;
  Serial.println("") ;
  Serial.println("Setup...") ;
  StateCommG[0] = 1 ;
  StateCommG[1] = 1 ;
  StateCommG[2] = 0 ;

  for(i=0; i<=3; i++){
      lastButState[i] = 0 ;
  }
/*  for(i = 23; i <= 35; i++){
    pinMode(i, OUTPUT) ;
  }*/
  
  pinMode(Eaubut, INPUT) ;
  pinMode(Cafebut, INPUT) ;
  pinMode(Sucrebut, INPUT) ;
  pinMode(Confirmationbut, OUTPUT) ;
  Serial.println("Fin Setup") ;
}

void ModStateComm(int Eau, int Cafe, int Sucre){//fonction du changement des states du café, du sucre et de l'eau
  
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

void loop() {
  butState[0] = digitalRead(Eaubut) ;
  butState[1] = digitalRead(Cafebut) ;
  butState[2] = digitalRead(Sucrebut) ;
  confirmation = digitalRead(Confirmationbut) ;

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
