
const int PanelRef = 25; //A1?
const int Panel = 26; //A2?
const int ISense = A2;
const int ISenseRef = A3;
int sec = 0;
float VPanel1000;
float VPanel;
float VPanelRef1000;
float VPanelRef;

void setup() {


}

void loop() {
  // Alle Spannungen komisch in lesbare Werte konvertieren(Hauptsache es funktioniert...)
  VPanel1000 = map(analogRead(Panel), 0, 1023, 0, 1000);
  VPanel = VPanel1000 / 200;
  VPanelRef1000 = map(analogRead(PanelRef), 0, 1023, 0, 1000);
  VPanelRef = VPanelRef1000 / 200;
  
  //Werte anzeigen
  Serial.print(analogRead(Panel)); Serial.print(" , "); Serial.println(VPanelRef); 
  
  delay(10000);
}
