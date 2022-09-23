
    // GPS
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
    // SD card
#include <SPI.h>
#include <SD.h>
    // temperature sensor
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


#define WRITE_INTERVAL 10000 // time between data points in ms

    // GPS
static const int RXPin = 8, TXPin = 9;
static const uint32_t GPSBaud = 9600;

SoftwareSerial ss(RXPin, TXPin);
TinyGPSPlus gps;

char taim[9];

    // SD
File myFile;

unsigned long lastWriteToSD;
char filepath[16];

    // bme
Adafruit_BME280 bme;

float temperature; // in °C
float pressure; // in hPa
float humidity; // in %


void setup() {
  // put your setup code here, to run once:
  ss.begin(GPSBaud);

  SD.begin(10);

  bme.begin(0x76);

  delay(100);
}

void loop() {
  
  // feed the gps object with incoming sentences  
  while (ss.available())
    gps.encode(ss.read());
  
  if(millis() > lastWriteToSD + WRITE_INTERVAL){
    writeDataPointToSD();
  }
}

void writeDataPointToSD(){
  lastWriteToSD = millis();
  updateTime();
  getTemperature();

  // this makes a new txt file each day
  memset(filepath, 0, sizeof(filepath)); // this completly clears the string for strcat

  if(gps.date.isValid()){
    sprintf(filepath, "%d-%d.txt", gps.date.day(), gps.date.month());
  } else {
    strcpy(filepath, "invalid.txt");
  }

  myFile = SD.open(filepath, FILE_WRITE);

  // time, lati, longi, alti, hdop position accuracy, speed, course, no of satellites, temperature, pressure, humidity
  myFile.print(taim); myFile.print(",");
  myFile.print(gps.location.lat(), 6); 
  myFile.print(",");
  myFile.print(gps.location.lng(), 6); 
  myFile.print(",");
  myFile.print(gps.altitude.meters()); 
  myFile.print(",");
  myFile.print(gps.hdop.value()); 
  myFile.print(",");
  myFile.print(gps.speed.mps()); 
  myFile.print(",");
  myFile.print(gps.course.deg()); 
  myFile.print(",");
  myFile.print(gps.satellites.value()); 
  myFile.print(",");
  myFile.print(temperature); 
  myFile.print(",");
  myFile.print(pressure); 
  myFile.print(",");
  myFile.print(humidity);
  myFile.println();  

  myFile.close();  
}

void updateTime() {

  if(gps.time.isValid()){
    sprintf(taim, "%02d:%02d:%02d", gps.time.hour(), gps.time.minute(), gps.time.second());
  } else {
    strcpy(taim, "xx:xx:xx");
  }
}


void getTemperature(){
    // this is needed in forced mode
    bme.takeForcedMeasurement();
    delay(2);

    temperature = bme.readTemperature();
    pressure = bme.readPressure() / 100.0F;
    humidity = bme.readHumidity();
}
