#define POTI_PIN A1

int voltage;

void setup() {
    Serial.begin(115200);

    pinMode(POTI_PIN, INPUT);
}

void loop() {
    voltage = analogRead(POTI_PIN);

    Serial.print(voltage);

    if(voltage > 990){
        Serial.print("\tDamn bro!");
    }
    if(voltage < 50){
        Serial.print("\tThat's weak, I expected more from you");
    }
    Serial.println();

    delay(500);
    
}