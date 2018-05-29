#include <AFMotor.h>


AF_Stepper cafe(200, 1);
AF_Stepper sucre(200, 2);


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");
  
  cafe.setSpeed(100);
  sucre.setSpeed(100);
}
 
void loop() {
  cafe.step(5000, FORWARD, DOUBLE) ;
  cafe.release() ;
  sucre.step(5000, FORWARD, DOUBLE) ;
  sucre.release() ;
  delay(1000) ;
}
