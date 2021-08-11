#define WHEEL_HS_PIN 14
#define WHEEL_HIGH_CUTOFF 2000 // [ms]  any time delta higher than this will be invalid

#define SPEED_FACTOR 7713.23 // circumference in km times 3600000

#define WHEEL_COOLDOWN 96 // equivalent to 80kmh

#define WRITE_INTERVAL 3000 // how often in ms a new data point is written

unsigned long currentMillis;

unsigned long lastWrite;

int wheelHS;
unsigned long wheelLastTrigger;
float speed;

int normalWheelHS;


void setup() {

  Serial.begin(9600);
  Serial.println("Start");

  setupWheelHS();
}

void setupWheelHS(){
  long sumOfHS = 0;

  // the magnet must be far away from the HS during this "callibration"
  for(int i = 0; i < 100; i++){
    sumOfHS = sumOfHS + analogRead(WHEEL_HS_PIN);
    delay(1);
  }

  normalWheelHS = sumOfHS/100;
  
  Serial.println(normalWheelHS);
}


void loop() {

  currentMillis = millis();
  
  if(checkWheelHS()){ // make this more fancy so that crankTimeDelta is gradually moving towards a mean and not influenced by irregularities -> updatespeed is already fancy
        int dt = currentMillis - wheelLastTrigger; // with my current wheels, at a speed of 40km/h, the average time delta will be 180ms

        if(dt > WHEEL_COOLDOWN){
            wheelLastTrigger = currentMillis;
            updateSpeed(dt);
        }
        
  }


  if(currentMillis - lastWrite > WRITE_INTERVAL){
    lastWrite = currentMillis;
    Serial.print("\t");
    Serial.println(speed);
    speed = 0;
  
  }

  
}

bool checkWheelHS(){
    //int lastWheelHS = wheelHS;
    wheelHS = analogRead(WHEEL_HS_PIN);

    // if the value is different from the value without a magnet, return true
    int HSdelta = wheelHS - normalWheelHS;
    if( HSdelta < -3 || HSdelta > 3 ){
        return true;
    }
    return false;
}

void updateSpeed(int dt){
    if(dt < WHEEL_HIGH_CUTOFF){
        float fdt = float(dt);
        
        Serial.print(" speed updated. ");
        
        float speedNow = SPEED_FACTOR / fdt;
        Serial.println(speedNow);
        speed = speed + fdt/float(WRITE_INTERVAL) * speedNow;
    }
    else Serial.println("high cutoff ");
}
