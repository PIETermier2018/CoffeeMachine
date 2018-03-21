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
int CommEau = 0 ;
int CommCafe = 0 ;
int CommSucre = 0 ;
int Confirmation = 0;

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
/*  for(i = 23; i <= 35; i++){
    pinMode(i, OUTPUT) ;
  }*/
  
  pinMode(Eaubut, INPUT) ;
  pinMode(Cafebut, INPUT) ;
  pinMode(Sucrebut, INPUT) ;
  pinMode(Confirmationbut, INPUT) ;
  Serial.println("Fin Setup") ;
}

  int ModStateComm(int Eau, int Cafe, int Sucre){
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
  return StateCommG ;
}

void loop() {
  if(pressbut == 0){
    while((CommEau == 0 || CommCafe == 0 || CommSucre == 0 || Confirmation == 0) && pressbut == 0){
      CommEau = digitalRead(Eaubut) ;
      CommCafe = digitalRead(Cafebut) ;
      CommSucre = digitalRead(Sucrebut) ;
      Confirmation = digitalRead(Confirmationbut) ;
      if(CommEau == 1 || CommCafe == 1 || CommSucre == 1 || Confirmation == 1){
        pressbut = 1 ;
      }
    }
  }
  
  if(CommEau == 1 || CommCafe == 1 || CommSucre == 1){
    ModStateComm(CommEau, CommCafe, CommSucre) ;
  }

  Serial.print("Dose Eau : ") ;
  Serial.print(StateCommG[0]) ;
  Serial.print(" , Dose Cafe : ") ;
  Serial.print(StateCommG[1]) ;
  Serial.print(" , Dose Sucre : ") ;
  Serial.print(StateCommG[2]) ;
  Serial.print(" , Confirmation : ") ;
  Serial.println(Confirmation) ;

  while(pressbut == 1){
    if(CommEau == 0 && CommCafe == 0 && CommSucre == 0 || Confirmation == 1){
      pressbut = 0 ;
    }
    CommEau = digitalRead(Eaubut) ;
    CommCafe = digitalRead(Cafebut) ;
    CommSucre = digitalRead(Sucrebut) ;
    Confirmation = digitalRead(Confirmationbut) ;
  }
}
