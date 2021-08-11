
#define CRANK_HS_PIN 16 // A1
#define WHEEL_HS_PIN 15 // A2

#define WRITE_INTERVAL 5000 // [ms] how often a new data point is written (must be lower than ~32000 to prevent the sumOfDt variables from overflowing)

#define CRANK_SENSITIVITY 2 // the necessary deviation from idle state
#define CRANK_COOLDOWN 300 // [ms] any time delta lower than this will be invalid
#define CRANK_HIGH_CUTOFF 5000 // [ms] any time delta higher than this will be invalid
#define CRANK_FACTOR 60000.0 // makes the cadence be in rpm !SHOULD BE FLOAT!

#define WHEEL_SENSITIVITY 5 // the necessary deviation from idle state
#define WHEEL_COOLDOWN 96 // [ms] any time delta lower than this will be invalid (equvalent to a speed of 80km/h)
#define WHEEL_HIGH_CUTOFF 2000 // [ms] any time delta higher than this will be invalid
#define SPEED_FACTOR 7713.23 // 3'600'000 * wheel circumference in km
unsigned long lastWriteToSD;

    // crank hs
int idleCrankHS;
unsigned long crankLastTrigger;
float cadence;
unsigned int sumOfDtCrank;

    // wheel hs
int idleWheelHS;
unsigned long wheelLastTrigger;
float speed;
unsigned int sumOfDtWheel;

void setup() {
    Serial.begin(9600);

    
      // setup HSses (this will take 200ms)
    long sumOfHS = 0;
    // the magnet must be away from the HS during this "callibration"
    for(int i = 0; i < 100; i++){
        sumOfHS = sumOfHS + analogRead(WHEEL_HS_PIN);
        delay(1);
    }
    idleWheelHS = sumOfHS/100;

    sumOfHS = 0;
    for(int i = 0; i < 100; i++){
        sumOfHS = sumOfHS + analogRead(CRANK_HS_PIN);
        delay(1);
    }
    idleCrankHS = sumOfHS/100;

    Serial.println(idleCrankHS);
    Serial.println(idleWheelHS);
}

void loop() {

   unsigned long currentMillis = millis();

  if(checkCrankHS()){
      int dt = currentMillis - crankLastTrigger; // with high cadence of 100 per minute, the average time delta will be 600ms
      
    if(dt > CRANK_COOLDOWN){
      crankLastTrigger = currentMillis;
      updateCadence(dt);
    }
  }

  if(checkWheelHS()){
      int dt = currentMillis - wheelLastTrigger; // with my current wheels, at a speed of 40km/h, the average time delta will be 180ms
      
      if(dt > WHEEL_COOLDOWN){
          wheelLastTrigger = currentMillis;
          updateSpeed(dt);
      }
  }
  if(currentMillis - lastWriteToSD > WRITE_INTERVAL){
      lastWriteToSD = currentMillis;

      Serial.print("\t\t\tSpeed: ");
      Serial.print(speed);
      Serial.print(" Cadence: ");
      Serial.println(cadence);
    cadence = 0;

    speed = 0;
  }
}

bool checkCrankHS(){ // make as one func
    // if the value is different from the value without a magnet, return true
    int HSdelta = analogRead(CRANK_HS_PIN) - idleCrankHS;
    
    if( -CRANK_SENSITIVITY > HSdelta || HSdelta > CRANK_SENSITIVITY ){

        return true;
    }
    return false;
}

bool checkWheelHS(){
    // if the value is different from the value without a magnet, return true
    int HSdelta = analogRead(WHEEL_HS_PIN) - idleWheelHS;
    
    if( -WHEEL_SENSITIVITY > HSdelta || HSdelta > WHEEL_SENSITIVITY ){

        return true;
    }
    return false;
}

void updateCadence(int dt){
    if(dt < CRANK_HIGH_CUTOFF){
        float fdt = float(dt);

        float cadenceNow = CRANK_FACTOR / fdt;

        // in one write cycle (10s long), the sum of dt will equal 10s, thus cadence = 0 + 1 * result (over time)
        cadence = cadence + fdt/float(WRITE_INTERVAL) * cadenceNow;
    }
}

void updateSpeed(int dt){
    if(dt < WHEEL_HIGH_CUTOFF){
        float fdt = float(dt);

        float speedNow = SPEED_FACTOR / fdt;
        speed = speed + fdt/float(WRITE_INTERVAL) * speedNow;

    }
}
