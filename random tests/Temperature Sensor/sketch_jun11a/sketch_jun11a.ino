#include <Adafruit_BMP280.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>

// 1013.25 default
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP280 bme;

void setup() {
  Serial.begin(9600);

  for(uint16_t i = 0; i<256; i++){
    if(bme.begin(i)) Serial.println(i);
    delay(20);
  }
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  Serial.println("BME sucessfully initialised");
}

void loop() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println("*C");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure());
  Serial.println("Pa");

  // altitude is very inaccurate with the mean sealevelairpressure due to weather. One can compute the altitude afterwards with the historical weather data
  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println("m");



  Serial.println();
  delay(5000);
}
