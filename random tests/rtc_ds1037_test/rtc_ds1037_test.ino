#include "Wire.h"
#define DS1307_I2C_ADDRESS 0x68
/*
 * Array mit den Wochentagbezeichnungen.
 * Die erste Stelle ist 0 da die Wochentage bei 1 für Sonntag beginnen.  
 * Hier hätte man im Quellcode an der passenden Stelle auch den Zähler 
 * um 1 verringern können jedoch wird darunter die lesbarkeit leiden.
 */
String daysOfWeek[8] = {"","Sonntag","Montag","Dienstag","Mittwoch","Donnerstag","Freitag","Samstag"};
//Konvertiert eine normale Dezimalzahl zu einer binärcodierten Dezimalzahl.
byte decToBcd(byte val){
  return( (val/10*16) + (val%10) );
}
//Konvertiert Binärcodierte Dezimalzahl zu einer
//normalen Dezimalzahl.
byte bcdToDec(byte val){
  return( (val/16*10) + (val%16) );
}
void setup(){
  Wire.begin();
  Serial.begin(9600);
  /*
   * Um die Uhrzeit & das Datum initial zu setzen, muss die
   * nachfolgende Zeile auskommentiert werden.
   * 
   * Parameter der Funktion 
   * setDS1307 - Sekunden, Minuten, Stunden, Tag der Woche, Tag im Monat, Monat, Jahr
   * Der "Tag der Woche" ist im Englischen Format d.h. Sonntag = 1, Montag = 2 usw.
   * Der Wert für das Jahr wird im 2 stelligen Bereich eingegeben, 
   * dieser Code ist also noch für ca. 82 Jahre funktionsfähig. 
   */
  //setDS1307(00,13,18,2,2,5,22);
}
void setDS1307(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year){
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.write(decToBcd(second)); // setzt die Sekunden
  Wire.write(decToBcd(minute)); // setzt die Minuten
  Wire.write(decToBcd(hour)); // setzt die Stunden
  Wire.write(decToBcd(dayOfWeek)); // setzt den Wert für den Tag der Woche
  Wire.write(decToBcd(dayOfMonth)); // setzt den Wert für den Tag im Monat
  Wire.write(decToBcd(month)); // setzt den Monat
  Wire.write(decToBcd(year)); // setzt das Jahr
  Wire.endTransmission();
}
void readDS1307time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year){
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
  //Anfordern der ersten 7 Datenbyte  vom DS1307
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}
void displayTime(){
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  readDS1307time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  //Ausgeben des Zeitstempels auf dem seriellen Ausgang.
  Serial.print(daysOfWeek[dayOfWeek]);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print(".");
  Serial.print(month, DEC);
  Serial.print(".");
  Serial.print(year, DEC);
  Serial.print(" ");
  Serial.print(hour<10?"0":"");
  Serial.print(hour, DEC);
  Serial.print(":");
  Serial.print(minute<10?"0":"");
  Serial.print(minute, DEC);
  Serial.print(":");
  Serial.print(second<10?"0":"");
  Serial.print(second, DEC);
  Serial.println(" ");
}
void loop(){
  displayTime(); 
  delay(1000); //kleine Pause von 1 Sekunde
}
