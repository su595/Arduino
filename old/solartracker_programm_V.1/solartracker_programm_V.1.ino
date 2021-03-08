
//Die LDRs mit 22kO in Serie schalten

#include <CheapStepper.h>
// V1 und V2 sind die LDRs in vertikaler Richtung jeweils an Pin A0 und A1 angeschlossen. V1 ist über/unter? V2! Ebenso für H1 und H2
const int V1 = A0; //Vertikal Unten
const int V2 = A1; //Vertikal Oben
const int H1 = A2; //Horizontal Links (Aus Sicht Solarpanel)
const int H2 = A3; //Horizontal Rechts
const int PanelRef = A4;
const int Panel = A6;
const int CurrentSense = A5;
int sec = 0;
float VPanel1000;
float VPanel;
float VPanelRef1000;
float VPanelRef;
CheapStepper stepperV (8,9,10,11);
CheapStepper stepperH (7,6,5,4);

void setup() {
  Serial.begin(9600);
  
  pinMode(V1, INPUT);
  pinMode(V2, INPUT);
  pinMode(H1, INPUT);
  pinMode(H2, INPUT);
  
}

void loop() {

  // Alle Spannungen komisch in lesbare Werte konvertieren(Hauptsache es funktioniert...)
  VPanel1000 = map(analogRead(Panel), 0, 1023, 0, 1000);
  VPanel = VPanel1000 / 200;
  VPanelRef1000 = map(analogRead(PanelRef), 0, 1023, 0, 1000);
  VPanelRef = VPanelRef1000 / 200;
  
  //Werte anzeigen
  Serial.print(VPanel); Serial.print(" , "); Serial.println(VPanelRef); 
  
  // Position anpassen
  while(analogRead(V1) != analogRead(V2)) {
    if(analogRead(V1) < analogRead(V2)) {
      stepperV.step(true); // Muss noch angepasst werden
      if(analogRead(V1) - analogRead(V2) > 3){Serial.print("breakO"); break;}
      Serial.print("Oben ");
    }
    if(analogRead(V1) > analogRead(V2)) {
      stepperV.step(false);
      if(analogRead(V1) - analogRead(V2) < 3){Serial.print("breakU"); break;}
     delay(10);
    } 
  }
  
//  while(analogRead(H1) != analogRead(H2)) {
  //  if(analogRead(H1) < analogRead(H2)) {
    //  stepperH.step(true);
   //  Serial.print("Links ");
   // }
  //  if(analogRead(H1) > analogRead(H2)) {
    //  stepperH.step(false);
    //  Serial.print("Rechts ");
  //  delay(1);
   // }
 // }

  delay(1000);
}
