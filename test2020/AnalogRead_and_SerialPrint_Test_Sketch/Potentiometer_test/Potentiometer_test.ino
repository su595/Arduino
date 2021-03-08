
float PanelVoltageRaw = 0;
float PanelVoltage500 = 0;
float PanelVoltage = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(5, OUTPUT);
pinMode(26, INPUT);
pinMode(7, OUTPUT);

Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(5, HIGH);
  digitalWrite(7, LOW);
  
  PanelVoltageRaw = analogRead(26);
  PanelVoltage500 = map(PanelVoltageRaw, 0, 1023, 0, 1000);
  PanelVoltage = PanelVoltage500 / 200;
  Serial.print(PanelVoltage);
  Serial.print("   ");
  Serial.print(PanelVoltage500);
  Serial.print("   ");
  delay(1000);
}
