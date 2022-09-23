#define PIN 5
#define WAIT 60000

float hrs;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN, INPUT);
  delay(500);
}

void loop() {
  
  while(digitalRead(PIN)){
      hrs = (millis())/3600000.0;
      Serial.print("Current uptime:\t");
      Serial.print(hrs);
      Serial.println(" hours");
      delay(WAIT);
  }
  Serial.print("no digital read, last hrs was ");
  Serial.println(hrs);
  delay(WAIT);
}
