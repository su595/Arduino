
// Pin A4
#define ANALOG_IN 26
//Pin D2
#define LED_PIN 2
//Some threshold (float from 0 to 5) to turn on the LED
#define THRES 2.6

void setup() {
  Serial.begin(9600);
  
  pinMode(ANALOG_IN, INPUT);
  pinMode(LED_PIN, OUTPUT);

}

void loop() {
  digitalWrite(LED_PIN, LOW);
  
  int rawVoltage = analogRead(ANALOG_IN);
  Serial.print("8-bit Voltage: ");
  Serial.print(String(rawVoltage));

  float Voltage0to5 = rawVoltage / 204.6;
  
  Serial.print("    Voltage from 0 to 5V: ");
  Serial.println(String(Voltage0to5));

  if(Voltage0to5 > THRES){
    digitalWrite(LED_PIN, HIGH);
  }
  
  delay(500);
}
