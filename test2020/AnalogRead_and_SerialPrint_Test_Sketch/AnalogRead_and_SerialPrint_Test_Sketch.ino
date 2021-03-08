
const int solarpanel = A0;

float PanelVoltageRaw = 0;
float PanelVoltage500 = 0;
float PanelVoltage = 0;

void setup() {
 
pinMode(19, INPUT);
Serial.begin(9600);
}

void loop() {
 
  PanelVoltageRaw = analogRead(solarpanel);
  PanelVoltage500 = map(PanelVoltageRaw, 0, 1023, 0, 1000);
  PanelVoltage = PanelVoltage500 / 200;
  Serial.print(PanelVoltage);
  Serial.print( "   " );
  Serial.print(PanelVoltage500);
  Serial.print( "   " );
  delay(1000);
}
