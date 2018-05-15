#include <AFMotor.h>


AF_Stepper cafe(200, 1);


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");
  
  cafe.setSpeed(100);
}
 
void loop() {
  cafe.step(5000, FORWARD, DOUBLE) ;
  cafe.release() ;
  delay(1000) ;
}
