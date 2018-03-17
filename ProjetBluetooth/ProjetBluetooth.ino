#include <SoftwareSerial.h>

SoftwareSerial  blue(8, 9) ;

int CommStat ;
int ModEau = 0 ;
int ModCafe = 0 ;
int ModSucre = 0 ;

void setup(){
  Serial.begin(9600) ; //ordi
  
  blue.begin(9600) ; //module bt
  
}

void loop(){
    CommStat = blue.read() ;
    
    if(CommStat != -1){
      ModSucre = ((CommStat-1)/15)+1 ; //c pour a et b
      ModCafe = ((CommStat-(ModSucre-1)*5*3-1)/5)+1 ; //b
      ModEau = CommStat-(ModSucre-1)*15-(ModCafe-1)*5 ; //a
      ModSucre = ModSucre-1 ; //vrai valeur de c
      /*Serial.print("CommStat = ") ;
      Serial.print(CommStat) ;*/
      Serial.print("Eau = ") ; 
      Serial.print(ModEau) ;
      Serial.print(" , Cafe = ") ;
      Serial.print(ModCafe) ;
      Serial.print(" , Sucre = ") ;
      Serial.println(ModSucre) ;
    }
}
