#include <AFMotor.h>

AF_Stepper Cafe(2, 200) ;


void setup() {
  Cafe.setSpeed(100) ;
}

void loop() {
  Cafe.step(200, FORWARD, DOUBLE) ;
  Cafe.release() ;
  delay(1000) ;
}
