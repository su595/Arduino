#include <FastLED.h>

#define NUM_LEDS 144
#define DATA_PIN 14
// Determines the speed of the main loop
#define DELAY 100
// Determines the frequency of the drops (higher is less frequent)
#define RANDOM 10
// The "radius" of the drops (size 3 would mean 2*3+1 leds large) 
// MAXIMUM SIZE IS 5 (more wont make sense)
#define DROP_SIZE 2
// The speed at which the drops loose brightness
#define FADE_SPEED 1

#define CHSV_COLOR_H 50
#define CHSV_COLOR_S 100
#define CHSV_COLOR_V 255

// A global variable that is a list of our LEDs we can directly write a CHSV object to
CRGB leds[NUM_LEDS];


void setup() { 

  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();

}

void loop(){ 
  // Logic whether a new drop shall be created (by testing for random numbers)
  if(random(0, RANDOM) == 0){

    createDrop(random(0, NUM_LEDS));

  }

  FastLED.show();
  fadeAll();
  delay(DELAY);
}

void createDrop(int position){


  for(int i = DROP_SIZE; i--; i>0){
    leds[position - i] = CHSV(CHSV_COLOR_H, CHSV_COLOR_S, CHSV_COLOR_V);
    leds[position + i] = CHSV(CHSV_COLOR_H, CHSV_COLOR_S, CHSV_COLOR_V);
  }

  leds[position] = CHSV(CHSV_COLOR_H, CHSV_COLOR_S, CHSV_COLOR_V);

}

void fadeAll(){


}
