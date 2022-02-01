#include <FastLED.h>

#define NUM_LEDS 144
#define DATA_PIN 3
#define POTI_IN 14

#define COLOR 45, 120, 255

CRGB leds[NUM_LEDS];

void setup() { 
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
  pinMode(POTI_IN, INPUT);

  Serial.begin(9600);
  for(int math = 0; math < 255; math++){
    int mathRes = quadwave8(math);
    Serial.println(mathRes);
  }
}

void loop() { 
  
  Serial.println(math);
  
  fill_solid(&leds[5], 7, CHSV(COLOR));
  
  FastLED.show();
  delay(2000);

  
}
