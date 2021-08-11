/* Demonstration of Rtc_Pcf8563 Date Time individual functions. 
 * Set the clock to a time then loop over reading time and 
 * output the time and date to the serial console.
 *
 * I used a RBBB with Arduino IDE, the pins are mapped a 
 * bit differently. Change for your hw
 * SCK - A5, SDA - A4, INT - D3/INT1
 *
 * After loading and starting the sketch, use the serial monitor
 * to see the clock output.
 * 
 * setup:  see Pcf8563 data sheet.
 *         1x 10Kohm pullup on Pin3 INT
 *         No pullups on Pin5 or Pin6 (I2C internals used)
 *         1x 0.1pf on power
 *         1x 32khz chrystal
 *
 * Joe Robertson, jmr
 * orbitalair@gmail.com
 */ 
#include <Wire.h>
#include <Rtc_Pcf8563.h>

#define STOP 3
#define RESET 2

//init the real time clock
Rtc_Pcf8563 rtc;

void setup(){
  Serial.begin(9600);
  Serial.println("Start");

  pinMode(STOP, INPUT_PULLUP);
  pinMode(RESET, INPUT_PULLUP);  
}

void resetClock(){
  //clear out the registers
  // this resets the time!!! dont call this every setup!!
  rtc.initClock();
  
  //set a time to start with.
  //day, weekday, month, century(1=1900, 0=2000), year(0-99)
  rtc.setDate(17, 6, 7, 0, 21);
  //hr, min, sec
  rtc.setTime(18, 55, 0);
}

void loop(){

  if(!digitalRead(RESET)){ 
    resetClock(); 
    Serial.println("reset");
  }
  if(!digitalRead(STOP)){ 
    rtc.setTime(rtc.getHour(), rtc.getMinute(), rtc.getSecond() - 1); 
    Serial.println("plus");
  }

  
  
  Serial.print(rtc.formatDate());
  Serial.print(" ");
  Serial.println(rtc.formatTime());

  delay(1000);
}
