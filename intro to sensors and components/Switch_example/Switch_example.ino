#define LED_PIN 13
#define SWITCH_PIN 9

bool switch_State;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(SWITCH_PIN, INPUT_PULLUP);
}

void loop() {
    
    switch_State = digitalRead(SWITCH_PIN);

    if(switch_State){
        digitalWrite(LED_PIN, LOW);
    } else {
        digitalWrite(LED_PIN, HIGH);
    }
    
    delay(100);
    
}