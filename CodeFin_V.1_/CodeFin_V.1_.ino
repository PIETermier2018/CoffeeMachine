#include <SoftwareSerial.h>
#include <AFMotor.h>

int Rx = 52 ;
int Tx = 53 ;

AF_Stepper Cafe(1, 200) ;
AF_Stepper Sucre(2, 200) ;

SoftwareSerial blue(Rx, Tx) ;

void setup() {
  
}

void loop() {
  
}
