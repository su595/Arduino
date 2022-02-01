#include <FastLED.h>

#define NUM_LEDS 292
#define DATA_PIN 19
// Determines the speed of the main loop
#define DELAY 1
// Determines the frequency of the drops (higher is less frequent)
#define RANDOM 100

// The speed at which the drops loose brightness (the larger the slower)
#define FADE_SPEED 250

#define CHSV_COLOR_H 175
#define CHSV_COLOR_S 200
#define CHSV_COLOR_V 255

// A global variable that is a list of our LEDs we can directly write CHSV objects to
CRGB leds[NUM_LEDS];


void setup() { 

  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();

  Serial.begin(9600);

}

void loop(){ 
  // whether a new drop shall be created by testing for random numbers
  if(random(0, RANDOM) == 0){
    createDrop(random(0, NUM_LEDS));
  }

  FastLED.show();
  fadeAll();     
  delay(DELAY);
}

void createDrop(int position){
  Serial.println("drop");
  
  leds[position - 3] = CHSV(CHSV_COLOR_H, CHSV_COLOR_S, CHSV_COLOR_V * 0.3);
  leds[position - 2] = CHSV(CHSV_COLOR_H, CHSV_COLOR_S, CHSV_COLOR_V * 0.6);
  leds[position - 1] = CHSV(CHSV_COLOR_H, CHSV_COLOR_S, CHSV_COLOR_V * 0.8);
  leds[position] = CHSV(CHSV_COLOR_H, CHSV_COLOR_S, CHSV_COLOR_V);
  leds[position + 1] = CHSV(CHSV_COLOR_H, CHSV_COLOR_S, CHSV_COLOR_V * 0.8);
  leds[position + 2] = CHSV(CHSV_COLOR_H, CHSV_COLOR_S, CHSV_COLOR_V * 0.6);
  leds[position + 3] = CHSV(CHSV_COLOR_H, CHSV_COLOR_S, CHSV_COLOR_V * 0.3);

}

void fadeAll(){ 
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i].nscale8(FADE_SPEED); 
  } 
}
