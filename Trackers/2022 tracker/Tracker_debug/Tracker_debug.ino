#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 8, TXPin = 9;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

    // temperature sensor

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

    // bme
float temperature; // in °C
float pressure; // in hPa
float humidity; // in %
Adafruit_BME280 bme;

uint32_t last_millis = 0;
bool mode = false;

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
  
  Serial.print("here");
  
  if(!bme.begin(0x76)){
    Serial.println("BME init fail"); 
  }

  // this sets the BME to forced mode, where it sleeps until I call bme.takeForcedMeasurement()
    bme.setSampling(Adafruit_BME280::MODE_FORCED,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X1, // pressure
                    Adafruit_BME280::SAMPLING_X1, // humidity
                    Adafruit_BME280::FILTER_OFF);

}

void loop()
{
  
  while (ss.available()) gps.encode(ss.read());
  
   
  if(gps.satellites.isValid()){ Serial.print("Satellites: "); Serial.print(gps.satellites.value());}
  
  
  if(gps.location.isValid()){ Serial.print("\tLat: "); Serial.print(gps.location.lat());}
  
  if(gps.location.isValid()){ Serial.print("\tLon: ");  Serial.print(gps.location.lng());}
  
  if(gps.location.isValid()){ Serial.print("\tLocation Age: "); Serial.print(gps.location.age());}
  
  Serial.print("\tDateTime:\t"); printDateTime(gps.date, gps.time);
  
  Serial.print("\tAltitude:\t"); 
  if(gps.altitude.isValid()) Serial.print(gps.altitude.meters());
  
  Serial.print("\tCourse:\t"); 
  if(gps.course.isValid()) Serial.print(gps.course.deg());
  
  Serial.print("\tSpeed:\t"); 
  if(gps.speed.isValid()) Serial.print(gps.speed.kmph());

  Serial.println();
  getTemperature();

  Serial.print("\tTemperature:\t"); 
  Serial.print(temperature);

  Serial.print("\tPressure:\t"); 
  Serial.print(pressure);

  Serial.print("\tHumidity:\t"); 
  Serial.print(humidity);

  Serial.println();
  smartDelay(5000);


}

void getTemperature(){
    // this is needed in forced mode
    bme.takeForcedMeasurement();
    delay(2);

    temperature = bme.readTemperature();
    pressure = bme.readPressure() / 100.0F;
    humidity = bme.readHumidity();
}


// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  if(d.isValid()) Serial.println(d.age());
  smartDelay(0);
}
