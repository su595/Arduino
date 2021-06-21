

// -------------RTC

#include <Rtc_Pcf8563.h>

Rtc_Pcf8563 rtc;

// -------------Temp

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

// -------------Main

#include <Wire.h>

// pin definitions

#define CRANK_HS_PIN 1
#define WHEEL_HS_PIN 2
#define MPU 0x68

// constants

#define WRITE_INTERVAL 10000 // how often in ms a new data point is written

// this has a big impact on sampling rate of crank and wheel, because loops per second for 1 is 308, for 10 is 3169 and for 100 is 4169
#define MPU_UPDATE_FREQUENCY 10 // how often in ms the MPU values are sampled (since this is quite computation intensive)

#define CRANK_SENSITIVITY 40 // from 0 to 1023 the difference when checkCrankHS gets triggered
#define CADENCE_LOW_CUTOFF 150 // any time delta lower than this will be invalid
#define CADENCE_HIGH_CUTOFF 5000 // any time delta higher than this will be invalid

#define WHEEL_SENSITIVITY 40 // from 0 to 1023 the difference when checkWheelHS gets triggered
#define WHEEL_LOW_CUTOFF 50 // any time delta lower than this will be invalid
#define WHEEL_HIGH_CUTOFF 2000 // any time delta higher than this will be invalid
#define SPEED_FACTOR 7350 // 3'600'000 * wheel circumference in km

// global variables

int crankHS = 0;
unsigned long crankLastTrigger = 0;
float cadence = 0;

int wheelHS = 0;
unsigned long wheelLastTrigger = 0;
float speed = 0;

float averageAccX, averageAccY, averageAccZ, averageRoll, averagePitch, averageYaw;
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
unsigned long lastMPU = 0;

unsigned long lastWriteToSD = 0;

float temperature, pressure, humidity;


void setup(){
    Serial.begin(38400); // debug serial
    Wire.begin();

    if(!bme.begin(0x76)){
        Serial.println(F("bme setup error"));
    }

    setupRTC();
    
    setupMPU();
}

// speed test
unsigned long loopsPerSec = 0;

void loop(){
    loopsPerSec++;

    // after fifty days of continious looping, this program will bug, but that's unlikely
    unsigned long currentMillis = millis(); // this assumes the whole loop happens at one time  

    if(checkCrankHS()){ // make this more fancy so that crankTimeDelta is gradually moving towards a mean and not influenced by irregularities
        int dt = currentMillis - crankLastTrigger; // with high cadence of 100 per minute, the average time delta will be 600ms
        crankLastTrigger = currentMillis;
        updateCadence(dt);
    }

    if(checkWheelHS()){ // make this more fancy so that crankTimeDelta is gradually moving towards a mean and not influenced by irregularities
        int dt = currentMillis - wheelLastTrigger; // with my current wheels, at a speed of 40km/h, the average time delta will be 180ms
        wheelLastTrigger = currentMillis;
        updateSpeed(dt);
    }

    if(currentMillis - lastMPU > MPU_UPDATE_FREQUENCY){
        int dt = currentMillis - lastMPU;
        lastMPU = currentMillis;
        updateMPU(dt);
    }

    if(currentMillis - lastWriteToSD > WRITE_INTERVAL){
        lastWriteToSD = currentMillis;
        writeToSD();

        // speed test
        loopsPerSec = loopsPerSec /10; // write interval is 10s
        Serial.print("Loops per second: ");
        Serial.println(loopsPerSec);
        loopsPerSec = 0;

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

bool checkWheelHS(){
    int lastWheelHS = wheelHS;
    wheelHS = analogRead(WHEEL_HS_PIN);

    // if the absolute difference is significant, return true
    if(!(-WHEEL_SENSITIVITY < lastWheelHS-crankHS < WHEEL_SENSITIVITY)){
        return true;
    }
    return false;
}

void updateCadence(int dt){
    if(CADENCE_LOW_CUTOFF < dt < CADENCE_HIGH_CUTOFF){
        float result = 60000 / dt;
        // in one write cycle (10s long), the sum of dt will equal 10s, thus cadence = 0 + 1 * result (over time)
        cadence = cadence + dt/WRITE_INTERVAL * result;
    }
    // if dt is unrealistic/faulty, set cadence as -69 to indicate the value is false
    cadence = -69;
}

void updateSpeed(int dt){
    if(WHEEL_LOW_CUTOFF < dt < WHEEL_HIGH_CUTOFF){
        float result = SPEED_FACTOR / dt;
        speed = speed + dt/WRITE_INTERVAL * result;
    }
    speed = -69;
}

int a = 0; // debug
float sumOfFactor = 0;
void updateMPU(int dt){


    getMotionWithoutLib(dt);
    float factor = float(dt)/WRITE_INTERVAL;

    sumOfFactor = sumOfFactor + factor;


    a++; // debug
    if(a == MPU_UPDATE_FREQUENCY*30){ // debug
        Serial.print(AccX);
        Serial.print("/");
        Serial.print(AccY);
        Serial.print("/");
        Serial.print(AccZ);
        Serial.print("    ");
        
        // Print the values on the serial monitor
        Serial.print(roll);
        Serial.print("/");
        Serial.print(pitch);
        Serial.print("/");
        Serial.println(yaw);
        Serial.print("  ");
        Serial.println(factor);
        a = 0;
    }
    

    averageAccX = averageAccX + factor * AccX;
    averageAccY = averageAccY + factor * AccY;
    averageAccZ = averageAccZ + factor * AccZ;
    averageRoll = averageRoll + factor * roll;
    averagePitch = averagePitch + factor * pitch;
    averageYaw = averageYaw + factor * yaw;
}

void setupMPU() {
    //Wire.begin();                      // Initialize comunication (already in setup)
    Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
    Wire.write(0x6B);                  // Talk to the register 6B
    Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
    Wire.endTransmission(true);        //end the transmission
    /*
    // Configure Accelerometer Sensitivity - Full Scale Range (default +/- 2g)
    Wire.beginTransmission(MPU);
    Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
    Wire.write(0x10);                  //Set the register bits as 00010000 (+/- 8g full scale range)
    Wire.endTransmission(true);
    // Configure Gyro Sensitivity - Full Scale Range (default +/- 250deg/s)
    Wire.beginTransmission(MPU);
    Wire.write(0x1B);                   // Talk to the GYRO_CONFIG register (1B hex)
    Wire.write(0x10);                   // Set the register bits as 00010000 (1000deg/s full scale)
    Wire.endTransmission(true);
    delay(20);
    */
    // Call this function if you need to get the IMU error values for your module
    calculate_IMU_error();
    delay(20);
}

void getMotionWithoutLib(int dt) {
    // === Read acceleromter data === //

    Wire.beginTransmission(MPU);
    Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
    //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
    AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
    AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
    AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value
    // Calculating Roll and Pitch from the accelerometer data
    accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - AccErrorX; // AccErrorX ~(0.58) See the calculate_IMU_error()custom function for more details
    accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) - AccErrorY; // AccErrorY ~(-1.58)
    
    // === Read gyroscope data === //

    float elapsedTime = float(dt) / 1000; // Divide by 1000 to get seconds
    Wire.beginTransmission(MPU);
    Wire.write(0x43); // Gyro data first register address 0x43
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true); // Read 4 registers total, each axis value is stored in 2 registers
    GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
    GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
    GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
    // Correct the outputs with the calculated error values
    GyroX = GyroX - GyroErrorX; // GyroErrorX ~(-0.56)
    GyroY = GyroY - GyroErrorY; // GyroErrorY ~(2)
    GyroZ = GyroZ - GyroErrorZ; // GyroErrorZ ~ (-0.8)
    // Currently the raw values are in degrees per seconds, deg/s, so we need to multiply by sendonds (s) to get the angle in degrees
    gyroAngleX = gyroAngleX + GyroX * elapsedTime; // deg/s * s = deg
    gyroAngleY = gyroAngleY + GyroY * elapsedTime;
    yaw =  yaw + GyroZ * elapsedTime;
    // Complementary filter - combine acceleromter and gyro angle values
    roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
    pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;
}

void calculate_IMU_error() {
    // We can call this funtion in the setup section to calculate the accelerometer and gyro data error. From here we will get the error values used in the above equations printed on the Serial Monitor.
    // Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
    // Read accelerometer values 200 times
    int c = 0;
    while (c < 200) {
        Wire.beginTransmission(MPU);
        Wire.write(0x3B);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU, 6, true);
        AccX = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
        AccY = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
        AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
        // Sum all readings
        AccErrorX = AccErrorX + ((atan((AccY) / sqrt(pow((AccX), 2) + pow((AccZ), 2))) * 180 / PI));
        AccErrorY = AccErrorY + ((atan(-1 * (AccX) / sqrt(pow((AccY), 2) + pow((AccZ), 2))) * 180 / PI));
        c++;
    }
    //Divide the sum by 200 to get the error value
    AccErrorX = AccErrorX / 200;
    AccErrorY = AccErrorY / 200;
    c = 0;
    // Read gyro values 200 times
    while (c < 200) {
        Wire.beginTransmission(MPU);
        Wire.write(0x43);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU, 6, true);
        GyroX = Wire.read() << 8 | Wire.read();
        GyroY = Wire.read() << 8 | Wire.read();
        GyroZ = Wire.read() << 8 | Wire.read();
        // Sum all readings
        GyroErrorX = GyroErrorX + (GyroX / 131.0);
        GyroErrorY = GyroErrorY + (GyroY / 131.0);
        GyroErrorZ = GyroErrorZ + (GyroZ / 131.0);
        c++;
    }
    //Divide the sum by 200 to get the error value
    GyroErrorX = GyroErrorX / 200;
    GyroErrorY = GyroErrorY / 200;
    GyroErrorZ = GyroErrorZ / 200;
    // Print the error values on the Serial Monitor
    Serial.print("AccErrorX: ");
    Serial.println(AccErrorX);
    Serial.print("AccErrorY: ");
    Serial.println(AccErrorY);
    Serial.print("GyroErrorX: ");
    Serial.println(GyroErrorX);
    Serial.print("GyroErrorY: ");
    Serial.println(GyroErrorY);
    Serial.print("GyroErrorZ: ");
    Serial.println(GyroErrorZ);
}

void getTemperature(){
    temperature = bme.readTemperature();
    pressure = bme.readPressure() / 100.0F;
    humidity = bme.readHumidity();
}

void setupSD(){

}

void writeToSD(){
    // after these global values have been written, they need to be reset to 0

    getTemperature();

    // 638 bytes of global variables without F()
    // 536 with everything in F

    Serial.print(rtc.formatTime());
    Serial.print(", ");
    Serial.println(rtc.formatDate());

    Serial.print(F("Cadence: "));
    Serial.print(cadence);
    Serial.print(F(", Speed: "));
    Serial.print(speed);
    Serial.print(F(", Average Acc: "));
    Serial.print(averageAccX);
    Serial.print(F(", "));
    Serial.print(averageAccY);
    Serial.print(F(", "));
    Serial.print(averageAccZ);
    Serial.print(F(", Average Rotation: "));
    Serial.print(averageRoll);
    Serial.print(F(", "));
    Serial.print(averagePitch);
    Serial.print(F(", "));
    Serial.print(averageYaw);
    Serial.print(F(", Temperature: "));
    Serial.print(temperature);
    Serial.print(F(", Pressure: "));
    Serial.print(pressure);
    Serial.print(F(", Humidity: "));
    Serial.print(humidity);
    Serial.print(F(" sum of factor: "));
    Serial.print(sumOfFactor);

    Serial.println();

    cadence = 0;
    speed = 0;

    averageAccX = 0;
    averageAccY = 0;
    averageAccZ = 0;
    averageRoll = 0;
    averagePitch = 0;
    averageYaw = 0;

    sumOfFactor = 0;

}




void setupRTC()
{
  //clear out the registers
  rtc.initClock();
  //set a time to start with.
  //day, weekday, month, century(1=1900, 0=2000), year(0-99)
  rtc.setDate(20, 6, 6, 0, 21);
  //hr, min, sec
  rtc.setTime(17, 59, 30);
}
