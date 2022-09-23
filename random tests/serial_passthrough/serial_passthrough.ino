#include <SoftwareSerial.h>


static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;

SoftwareSerial ss(RXPin, TXPin);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ss.begin(GPSBaud);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()) ss.write(Serial.read());

  if(ss.available()) Serial.write(ss.read());
}
