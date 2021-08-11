#define SWITCH_OUT 3 // D3 / Interrupt1
#define SWITCH_IN 2 // D2 / Interrupt0

#include <avr/sleep.h>
#include <avr/power.h>

volatile bool isSwitchTriggered;
uint8_t state;

void setup() {
    Serial.begin(9600);
    pinMode(SWITCH_IN, INPUT_PULLUP); attachInterrupt(digitalPinToInterrupt(SWITCH_IN), switchISR, CHANGE);
    pinMode(SWITCH_OUT, INPUT_PULLUP); attachInterrupt(digitalPinToInterrupt(SWITCH_OUT), switchISR, CHANGE);
    isSwitchTriggered = true; // measure the switch states once at the beginning
}

void loop() {

    if(isSwitchTriggered){
        updateState();
        isSwitchTriggered = false;
    }

    switch(state){
        case 0: // out: oben, in: oben
            Serial.println("case 0");

            break;
        case 1: // out: oben, in: unten
            Serial.println("case 1");


            // the arduino will wakeup as soon as any interrupt is triggered
            delay(100);
            set_sleep_mode(SLEEP_MODE_PWR_DOWN);
            sleep_enable();
            sleep_mode();
            
            /* The program will continue from here. */
            /* First thing to do is disable sleep. */
            sleep_disable(); 

            Serial.println("wakeup");

            break;
        case 2: // out: unten, in: oben
            Serial.println("case 2");

            break;
        case 3: // out: unten, in: unten
            Serial.println("case 3");

            break;
        default:
            isSwitchTriggered = true;
    }
    delay(500);  
}

void switchISR(){
    isSwitchTriggered = true;
}

void updateState(){
    state = (digitalRead(SWITCH_OUT) << 1) + digitalRead(SWITCH_IN);

    Serial.print("state = ");
    Serial.println(state);
}
