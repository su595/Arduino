
#define LDR_PIN 14
#define LED_PIN 15
#define SCHWELLE 230 //Von 0 bis 1023
int ldrSpannung = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  ldrSpannung = analogRead(LDR_PIN);
  Serial.println(ldrSpannung);

  if(ldrSpannung < SCHWELLE){
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED an!");
  }
  else{
    digitalWrite(LED_PIN, LOW);
  }
  
  delay(1000);
}
