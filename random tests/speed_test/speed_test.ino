
// pin definitions
#define CRANK_HS_PIN 1
#define WHEEL_HS_PIN 2

// constants
#define CRANK_SENSITIVITY 40 // from 0 to 1023 the difference when checkCrankHS gets triggered
#define CADENCE_CUTOFF 10 // any cadence per minute lower than this will be invalid

#define WHEEL_SENSITIVITY 40 // from 0 to 1023 the difference when checkWheelHS gets triggered
#define VEL_CUTOFF 3 // any velocity in km/h lower than this will be invalid

// global variables
int crankHS = 0;
unsigned long crankLastTrigger = 0;
int crankTimeDelta = 0; // with high cadence of 100 per minute, the average time delta will be 600ms
int wheelHS = 0;
unsigned long currentMicros = 0;
unsigned int i = 0;

void setup() {
    Serial.begin(9600); // debug serial
}


void loop() {
    unsigned long lastMicros = currentMicros;
    currentMicros = micros();
    int delta = currentMicros - lastMicros;

    i++;
    if(i==20000){
        i = 0;
        Serial.print("uS per loop: ");
        Serial.println(delta);
        uint16_t loopsPerSec = 1000000/delta;
        Serial.print("Loops per second: ");
        Serial.println(loopsPerSec);
    }

   if(checkCrankHS()){
        crankTimeDelta = currentMicros*1000 - crankLastTrigger;
    }
}

bool checkCrankHS(){
    int lastCrankHS = crankHS;
    crankHS = analogRead(CRANK_HS_PIN);

    // if the absolute difference is significant, return true
    if(!(-CRANK_SENSITIVITY < lastCrankHS-crankHS < CRANK_SENSITIVITY)){
        return true;
    }
    return false;
}
