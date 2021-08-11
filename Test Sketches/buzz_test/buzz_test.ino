
#define BUZZER_EN 6 // D6
#define BUZZER_BASE 7 // D7
#define LED_PIN 4 // D4
#define SWITCH_OUT 3 // D3 / Interrupt1


void setup() {
    pinMode(BUZZER_EN, OUTPUT);
    pinMode(BUZZER_BASE, OUTPUT);
    digitalWrite(BUZZER_EN, LOW);
    digitalWrite(BUZZER_BASE, LOW);
    pinMode(SWITCH_OUT, INPUT_PULLUP);
}

void loop() {
   Buzzer(1, 1000 , false);
   Buzzer(2, 1000, true);

    delay(2000);

    while(digitalRead(SWITCH_OUT)){}

}



void Buzzer(uint8_t noOfPulses, unsigned int duration, bool loud){
    Serial.println(F("error :("));

    // this uses delay and will mess with the rest of the program, but since an error already occured, it doesn't really matter
    for(uint8_t i; i < noOfPulses; i++){
        digitalWrite(BUZZER_BASE, HIGH);
        if(loud) digitalWrite(BUZZER_EN, HIGH);
        digitalWrite(LED_PIN, HIGH);

        delay(duration);

        digitalWrite(BUZZER_BASE, LOW);
        digitalWrite(BUZZER_EN, LOW);
        digitalWrite(LED_PIN, LOW);
        delay(duration);
    }
}
