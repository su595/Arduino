#define LED_PIN 13

bool led_State;

void setup() {
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    
    if(led_State){
        digitalWrite(LED_PIN, LOW);
        led_State = false;
    } else {
        digitalWrite(LED_PIN, HIGH);
        led_State = true;
    }
    
    delay(1000);



    blinkLED(LED_PIN, 54, 477);
}



void blinkLED(int pin, int timeOn, int timeOff){
  digitalWrite(pin, HIGH);
  delay(timeOn);
  digitalWrite(pin, LOW);
  delay(timeOff);
}



// make a function that takes two integers and returns half of the difference
