#include <Wire.h>
#define MPU 0x68 // MPU6050 I2C address

#define WRITE_INTERVAL 10000 // [ms] how often a new data point is written (must be lower than ~32000 to prevent the sumOfDt variables from overflowing)
#define MPU_UPDATE_FREQUENCY 100 // [ms] how often the MPU values are sampled (since this is quite computation intensive)

float AccX, AccY, AccZ;
//float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float averageAccX, averageAccY, averageAccZ, averageRoll, averagePitch, averageYaw;
unsigned long lastMPU = 0;

void setupMPU() {
    Serial.begin(9600);
    
    Wire.begin();                      // Initialize comunication
    Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
    Wire.write(0x6B);                  // Talk to the register 6B
    Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
    Wire.endTransmission(true);        // end the transmission

    // Call this function if you need to get the IMU error values for your module
    delay(30);
    calculate_IMU_error();
    delay(20);
    
}


void getMotionWithoutLib() {
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
    float accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) ; // AccErrorX ~(0.58) See the calculate_IMU_error()custom function for more details
    float accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) ; // AccErrorY ~(-1.58)
    
    // === Read gyroscope data === //

    float elapsedTime = float(dt) / 1000; // Divide by 1000 to get seconds
    Wire.beginTransmission(MPU);
    Wire.write(0x43); // Gyro data first register address 0x43
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true); // Read 4 registers total, each axis value is stored in 2 registers
    float GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
    float GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
    float GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
    // Correct the outputs with the calculated error values
    //GyroX = GyroX - 0.33; // GyroErrorX ~(-0.56)
    //GyroY = GyroY - 3.99; // GyroErrorY ~(2)
    //GyroZ = GyroZ + 0.02; // GyroErrorZ ~ (-0.8)
    // Currently the raw values are in degrees per seconds, deg/s, so we need to multiply by sendonds (s) to get the angle in degrees
    roll = roll + GyroX * elapsedTime; // deg/s * s = deg
    pitch = pitch + GyroY * elapsedTime;
    yaw =  yaw + GyroZ * elapsedTime;
    // Complementary filter - combine acceleromter and gyro angle values
    roll = 0.92 * roll + 0.08 * accAngleX;
    pitch = 0.92 * pitch + 0.08 * accAngleY;
}

void calculate_IMU_error() {
    // We can call this funtion in the setup section to calculate the accelerometer and gyro data error. From here we will get the error values used in the above equations printed on the Serial Monitor.
    // Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
    // Read accelerometer values 200 times
    float AccErrorX = 0;
    float AccErrorY = 0;
    float GyroErrorX = 0;
    float GyroErrorY = 0;
    float GyroErrorZ = 0;

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
        float GyroX = Wire.read() << 8 | Wire.read();
        float GyroY = Wire.read() << 8 | Wire.read();
        float GyroZ = Wire.read() << 8 | Wire.read();
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
<<<<<<< HEAD
=======

void loop(){
    unsigned long currentMillis = millis();

    if(currentMillis - lastMPU > 10){
        lastMPU = currentMillis;
        loopMPU();
    }
}
>>>>>>> ececbecd205f41a9d67435861a9fcf0ebe28ca04
