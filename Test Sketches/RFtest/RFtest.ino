#include <RCSwitch.h>

RCSwitch myEmitter = RCSwitch();
RCSwitch myReceiver = RCSwitch();

void setup() {
  Serial.begin(9600);

  myEmitter.enableTransmit(10);  // Der Sender wird an Pin 10 angeschlossen
  myReceiver.enableReceive(0);  // Empfänger ist an Interrupt-Pin "0" - Das ist am UNO der Pin2
}

void loop() {
  myEmitter.send(1234, 24); // Der 433mhz Sender versendet die Dezimalzahl „1234“
  delay(1);
  
  if (myReceiver.available()) // Wenn ein Code Empfangen wird...
  {
    int value = myReceiver.getReceivedValue(); // Empfangene Daten werden unter der Variable "value" gespeichert.
  
    if (value == 0) // Wenn die Empfangenen Daten "0" sind, wird "Unbekannter Code" angezeigt.
    {
      Serial.println("Unbekannter Code");
    } 
    
    else // Wenn der Empfangene Code brauchbar ist, wird er hier an den Serial Monitor gesendet.
    {
      Serial.print("Empfangen: ");
      Serial.println( myReceiver.getReceivedValue() );
    }

    myReceiver.resetAvailable(); // Hier wird der Empfänger "resettet"
  }

  Serial.println("loop");
  delay(1000);  // Eine Sekunde Pause, danach startet der Sketch von vorne
}  
