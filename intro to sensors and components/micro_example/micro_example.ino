#define LED_PIN 13
#define MIC_PIN A2
#define SENSITIVITY 20

bool led_State;
int lastMic;
int mic;

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(MIC_PIN, INPUT);
}

void loop() {

    mic = analogRead(MIC_PIN);
    int delta = mic - lastMic;
    lastMic = mic;

    Serial.print(mic);

    if(abs(delta) > SENSITIVITY){
        if(led_State){
            digitalWrite(LED_PIN, LOW);
            led_State = false;
        } else {
            digitalWrite(LED_PIN, HIGH);
            led_State = true;
        }
    }
    
    delay(1);
}
