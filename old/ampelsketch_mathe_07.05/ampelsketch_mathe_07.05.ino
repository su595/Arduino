
const int LEDRot = 1; //Muss angepasst werden
const int LEDGelb = 2;
const int LEDGrun = 3;
const int Ampeltaster = 4;
const int IntervallZeit = 2000; //in ms

void setup() {
  pinMode(LEDRot, OUTPUT);
  pinMode(LEDGelb, OUTPUT);
  pinMode(LEDGrun, OUTPUT);
  pinMode(Ampeltaster, INPUT);
  
}

void loop() {
  digitalWrite(LEDRot, HIGH);
  if(digitalRead(Ampeltaster == HIGH)){
    digitalWrite(LEDGelb, HIGH);
    delay(200);
    digitalWrite(LEDRot, LOW);
    digitalWrite(LEDGelb, LOW);
    digitalWrite(LEDGrun, HIGH);
    delay(IntervallZeit);
    digitalWrite(LEDGrun, LOW);
    digitalWrite(LEDGelb, HIGH);
    delay(200);
    digitalWrite(LEDGelb, LOW);
    }
  
}
