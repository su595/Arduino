// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#endif

#define ledstrip 6
#define lichtsensor 0
#define anzahlframes 15

int zeit = 0;
int i = 0;
int frametime = 0;
char framenumber[7];

Adafruit_NeoPixel pixels(8, ledstrip, NEO_GRB + NEO_KHZ800);


void setup() {

  pinMode(lichtsensor, INPUT);

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  //Lichtsensor der einmal pro Umdrehung anschlägt, hier wird die Zeit einer Umdrehung zehnmal gemessen
  for (zeit = 0; i<10; zeit++) {
    if (digitalRead(lichtsensor) == HIGH) {i++;}
    delay(1);
  }
  zeit = zeit/10;
  frametime = 33/zeit;
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  i = 0;
  reset:
  for(; i<10; i++){
    framenumber = {"frame", 'i'}
    delay(frametime);
    goto framenumber;
    }

}

frame0:

pixels.setPixelColor(0, pixels.Color(0, 150, 0));
pixels.setPixelColor(1, pixels.Color(0, 150, 0));
pixels.setPixelColor(2, pixels.Color(0, 150, 0));
pixels.setPixelColor(3, pixels.Color(0, 150, 0));
pixels.setPixelColor(4, pixels.Color(0, 150, 0));
pixels.setPixelColor(5, pixels.Color(0, 150, 0));
pixels.setPixelColor(6, pixels.Color(0, 150, 0));
pixels.setPixelColor(7, pixels.Color(0, 150, 0));
pixels.setPixelColor(8, pixels.Color(0, 150, 0));  
pixels.show();

goto reset;


frame1:

pixels.setPixelColor(0, pixels.Color(0, 150, 0));
pixels.setPixelColor(1, pixels.Color(0, 150, 0));
pixels.setPixelColor(2, pixels.Color(0, 150, 0));
pixels.setPixelColor(3, pixels.Color(0, 150, 0));
pixels.setPixelColor(4, pixels.Color(0, 150, 0));
pixels.setPixelColor(5, pixels.Color(0, 150, 0));
pixels.setPixelColor(6, pixels.Color(0, 150, 0));
pixels.setPixelColor(7, pixels.Color(0, 150, 0));
pixels.setPixelColor(8, pixels.Color(0, 150, 0));  
pixels.show();

goto reset;


frame2:

pixels.setPixelColor(0, pixels.Color(0, 150, 0));
pixels.setPixelColor(1, pixels.Color(0, 150, 0));
pixels.setPixelColor(2, pixels.Color(0, 150, 0));
pixels.setPixelColor(3, pixels.Color(0, 150, 0));
pixels.setPixelColor(4, pixels.Color(0, 150, 0));
pixels.setPixelColor(5, pixels.Color(0, 150, 0));
pixels.setPixelColor(6, pixels.Color(0, 150, 0));
pixels.setPixelColor(7, pixels.Color(0, 150, 0));
pixels.setPixelColor(8, pixels.Color(0, 150, 0));  
pixels.show();

goto reset;
