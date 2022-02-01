
#define trigger 3
#define echo 2


void setup() {
  Serial.begin(115200);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {

  getDistance();
  delay(1000);

}

void getDistance(){
  
  // send a trigger pulse of 10us
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // measure the length of the echo pulse
  unsigned long pulseLength = pulseIn(echo, HIGH);
  
  Serial.print(pulseLength);
  Serial.print("   ");
  
  int distance = pulseLength * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  Serial.println(distance);
}
