#include <CheapStepper.h>
CheapStepper stepper1 (8,9,10,11);
CheapStepper stepper2 (7,6,5,4);

boolean clockwise = true;
int a=0;

void setup() {
  Serial.begin(9600);
    
}

void loop() {
  for(a=0; a<2048; a++){
    stepper1.step(clockwise);
    stepper2.step(clockwise);
    clockwise = !clockwise;
  }
  delay(1000);
}
