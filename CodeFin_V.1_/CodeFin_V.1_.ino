#include <SoftwareSerial.h>
#include <AFMotor.h>

//init port Serie bluetooth
//int Rx = 52 ;
//int Tx = 53 ;

//init variables divers : 
int i ;

//SoftwareSerial blue(Rx, Tx) ;

//init variables broches : 
int Eaubut = 49 ;
int Cafebut = 50 ;
int Sucrebut = 51 ;

//init variables commandes :
int CommEau ;
int CommCafe ;
int CommSucre ;

int StateComm[3] ;

AF_Stepper Cafe(1, 200) ;
AF_Stepper Sucre(2, 200) ;

void setup() {
  Serial.begin(9600) ;
  Serial.println("Setup...") ;
  for(i = 23; i <= 35; i++){
    pinMode(i, OUTPUT) ;
  }
  
  pinMode(Eaubut, INPUT) ;
  pinMode(Cafebut, INPUT) ;
  pinMode(Sucrebut, INPUT) ;
  Serial.println("Lancement loop...") ;
}

void loop() {
  CommEau = digitalRead(Eaubut) ;
  CommCafe = digitalRead(Cafebut) ;
  CommSucre = digitalRead(Sucrebut) ;

  Serial.print("CommEau : ") ;
  Serial.print(CommEau) ;
  Serial.print(" , CommCafe : ") ;
  Serial.print(CommCafe) ;
  Serial.print(" , CommSucre : ") ;
  Serial.println(CommSucre) ;
}
