#include <SoftwareSerial.h>

// Choose two Arduino pins to use for software serial
int RXPin = 2;
int TXPin = 3;

//Default baud of NEO-6M is 9600
int GPSBaud = 9600;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup()
{
  // Start the Arduino hardware serial port at 115200 baud
  Serial.begin(115200);

  // Start the software serial port at the GPS's default baud
  gpsSerial.begin(GPSBaud);

  Serial.print("test");
}

unsigned long lastMillis = 0;
void loop(){
  
  // Displays information when new sentence is available.
  while (gpsSerial.available() > 0){
    byte by = gpsSerial.read();

    // after a 200ms delay we assume it is a new cluster of sentences
    if(millis() - lastMillis > 200 ){
      lastMillis = millis();
      Serial.print("-----------");
    }

    // if a new sentence begins, print a new line
    if(by == '$'){
      Serial.println();
    }
    
    Serial.write(by);
  }
    
}
