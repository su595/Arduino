const int Phresistor = 14;
const int uThreshold = 400
const int timer = 0;

void setup() {

  
}

void loop() {
  delay(1);
  timer++;
  if(analogRead(Phresistor) < uThreshold){
    timestamp = timer;
    }
  print(timestamp)

  
}
