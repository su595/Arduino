// i use uint8_t instead of int in various places throughout this script. This is just to save some ram, since an int takes two whereas a uint8_t takes only one byte
// this really only matters with the buffer list, where there's 432 uint8_t

#include <FastLED.h>

// number of LEDs on the led matrix. I can't gurantee it to work with values other than 144
#define NUM_LEDS 144

// data pin of the led matrix
#define DATA_PIN 14

// These should have NUM_LEDS * 3 entries (rgb for each led), if less expect random values, if more expect errors
const uint8_t l0[] PROGMEM = {0,0,0,25,25,25,79,79,79,24,25,25,12,18,21,112,107,102,109,106,103,14,21,25,0,0,0,0,0,0,32,32,32,22,22,22,51,51,51,73,73,73,28,32,35,77,78,79,201,151,115,255,135,51,255,138,56,211,152,109,123,113,104,36,41,44,26,27,27,17,17,17,9,8,8,42,44,45,174,145,123,254,149,75,255,108,4,254,103,0,254,103,0,255,106,0,255,128,35,240,167,115,67,67,66,0,0,0,0,0,2,170,137,112,255,123,21,255,102,0,254,106,0,254,106,0,254,106,0,254,106,0,254,103,0,255,118,15,145,124,108,0,0,0,13,18,24,215,139,83,255,103,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,255,107,2,199,147,109,5,10,13,58,59,60,246,137,59,255,103,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,255,102,0,235,146,82,36,41,46,126,113,103,255,125,30,254,104,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,103,0,254,135,49,97,93,90,83,79,77,248,139,60,255,102,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,102,0,255,132,38,146,136,127,0,3,5,162,132,109,255,117,16,254,105,0,254,106,0,254,106,0,254,106,0,254,106,0,254,104,0,255,114,14,191,143,108,30,32,34,0,0,0,31,35,38,230,149,91,255,103,0,254,105,0,254,105,0,254,105,0,254,104,0,255,110,5,210,148,102,26,31,34,0,0,0,0,0,0,0,0,0,107,96,88,255,143,59,255,121,25,255,121,23,255,116,15,255,117,17,221,145,88,42,44,47,0,0,0,0,0,0,0,0,0,0,0,0,7,9,10,109,99,93,120,103,92,129,110,96,144,117,98,146,121,102,61,60,58,0,0,0,0,0,0,0,0,0};
const uint8_t l1[] PROGMEM = {0,0,0,25,25,25,79,79,79,24,25,25,12,18,21,112,107,102,109,106,103,14,21,25,0,0,0,0,0,0,32,32,32,22,22,22,51,51,51,73,73,73,28,32,35,77,78,79,201,151,115,255,135,51,255,138,56,211,152,109,123,113,104,36,41,44,26,27,27,17,17,17,9,8,8,42,44,45,174,145,123,254,149,75,255,108,4,254,103,0,254,103,0,255,106,0,255,128,35,240,167,115,67,67,66,0,0,0,0,0,2,170,137,112,255,123,21,255,102,0,254,106,0,254,106,0,254,106,0,254,106,0,254,103,0,255,118,15,145,124,108,0,0,0,13,18,24,215,139,83,255,103,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,255,107,2,199,147,109,5,10,13,58,59,60,246,137,59,255,103,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,255,102,0,235,146,82,36,41,46,126,113,103,255,125,30,254,104,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,103,0,254,135,49,97,93,90,83,79,77,248,139,60,255,102,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,102,0,255,132,38,146,136,127,0,3,5,162,132,109,255,117,16,254,105,0,254,106,0,254,106,0,254,106,0,254,106,0,254,104,0,255,114,14,191,143,108,30,32,34,0,0,0,31,35,38,230,149,91,255,103,0,254,105,0,254,105,0,254,105,0,254,104,0,255,110,5,210,148,102,26,31,34,0,0,0,0,0,0,0,0,0,107,96,88,255,143,59,255,121,25,255,121,23,255,116,15,255,117,17,221,145,88,42,44,47,0,0,0,0,0,0,0,0,0,0,0,0,7,9,10,109,99,93,120,103,92,129,110,96,144,117,98,146,121,102,61,60,58,0,0,0,0,0,0,0,0,0};
const uint8_t l2[] PROGMEM = {0,0,0,25,25,25,79,79,79,24,25,25,12,18,21,112,107,102,109,106,103,14,21,25,0,0,0,0,0,0,32,32,32,22,22,22,51,51,51,73,73,73,28,32,35,77,78,79,201,151,115,255,135,51,255,138,56,211,152,109,123,113,104,36,41,44,26,27,27,17,17,17,9,8,8,42,44,45,174,145,123,254,149,75,255,108,4,254,103,0,254,103,0,255,106,0,255,128,35,240,167,115,67,67,66,0,0,0,0,0,2,170,137,112,255,123,21,255,102,0,254,106,0,254,106,0,254,106,0,254,106,0,254,103,0,255,118,15,145,124,108,0,0,0,13,18,24,215,139,83,255,103,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,255,107,2,199,147,109,5,10,13,58,59,60,246,137,59,255,103,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,255,102,0,235,146,82,36,41,46,126,113,103,255,125,30,254,104,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,103,0,254,135,49,97,93,90,83,79,77,248,139,60,255,102,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,102,0,255,132,38,146,136,127,0,3,5,162,132,109,255,117,16,254,105,0,254,106,0,254,106,0,254,106,0,254,106,0,254,104,0,255,114,14,191,143,108,30,32,34,0,0,0,31,35,38,230,149,91,255,103,0,254,105,0,254,105,0,254,105,0,254,104,0,255,110,5,210,148,102,26,31,34,0,0,0,0,0,0,0,0,0,107,96,88,255,143,59,255,121,25,255,121,23,255,116,15,255,117,17,221,145,88,42,44,47,0,0,0,0,0,0,0,0,0,0,0,0,7,9,10,109,99,93,120,103,92,129,110,96,144,117,98,146,121,102,61,60,58,0,0,0,0,0,0,0,0,0};
const uint8_t l3[] PROGMEM = {0,0,0,25,25,25,79,79,79,24,25,25,12,18,21,112,107,102,109,106,103,14,21,25,0,0,0,0,0,0,32,32,32,22,22,22,51,51,51,73,73,73,28,32,35,77,78,79,201,151,115,255,135,51,255,138,56,211,152,109,123,113,104,36,41,44,26,27,27,17,17,17,9,8,8,42,44,45,174,145,123,254,149,75,255,108,4,254,103,0,254,103,0,255,106,0,255,128,35,240,167,115,67,67,66,0,0,0,0,0,2,170,137,112,255,123,21,255,102,0,254,106,0,254,106,0,254,106,0,254,106,0,254,103,0,255,118,15,145,124,108,0,0,0,13,18,24,215,139,83,255,103,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,255,107,2,199,147,109,5,10,13,58,59,60,246,137,59,255,103,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,255,102,0,235,146,82,36,41,46,126,113,103,255,125,30,254,104,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,103,0,254,135,49,97,93,90,83,79,77,248,139,60,255,102,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,102,0,255,132,38,146,136,127,0,3,5,162,132,109,255,117,16,254,105,0,254,106,0,254,106,0,254,106,0,254,106,0,254,104,0,255,114,14,191,143,108,30,32,34,0,0,0,31,35,38,230,149,91,255,103,0,254,105,0,254,105,0,254,105,0,254,104,0,255,110,5,210,148,102,26,31,34,0,0,0,0,0,0,0,0,0,107,96,88,255,143,59,255,121,25,255,121,23,255,116,15,255,117,17,221,145,88,42,44,47,0,0,0,0,0,0,0,0,0,0,0,0,7,9,10,109,99,93,120,103,92,129,110,96,144,117,98,146,121,102,61,60,58,0,0,0,0,0,0,0,0,0};
const uint8_t l4[] PROGMEM = {0,0,0,25,25,25,79,79,79,24,25,25,12,18,21,112,107,102,109,106,103,14,21,25,0,0,0,0,0,0,32,32,32,22,22,22,51,51,51,73,73,73,28,32,35,77,78,79,201,151,115,255,135,51,255,138,56,211,152,109,123,113,104,36,41,44,26,27,27,17,17,17,9,8,8,42,44,45,174,145,123,254,149,75,255,108,4,254,103,0,254,103,0,255,106,0,255,128,35,240,167,115,67,67,66,0,0,0,0,0,2,170,137,112,255,123,21,255,102,0,254,106,0,254,106,0,254,106,0,254,106,0,254,103,0,255,118,15,145,124,108,0,0,0,13,18,24,215,139,83,255,103,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,255,107,2,199,147,109,5,10,13,58,59,60,246,137,59,255,103,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,255,102,0,235,146,82,36,41,46,126,113,103,255,125,30,254,104,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,103,0,254,135,49,97,93,90,83,79,77,248,139,60,255,102,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,102,0,255,132,38,146,136,127,0,3,5,162,132,109,255,117,16,254,105,0,254,106,0,254,106,0,254,106,0,254,106,0,254,104,0,255,114,14,191,143,108,30,32,34,0,0,0,31,35,38,230,149,91,255,103,0,254,105,0,254,105,0,254,105,0,254,104,0,255,110,5,210,148,102,26,31,34,0,0,0,0,0,0,0,0,0,107,96,88,255,143,59,255,121,25,255,121,23,255,116,15,255,117,17,221,145,88,42,44,47,0,0,0,0,0,0,0,0,0,0,0,0,7,9,10,109,99,93,120,103,92,129,110,96,144,117,98,146,121,102,61,60,58,0,0,0,0,0,0,0,0,0};
const uint8_t l5[] PROGMEM = {0,0,0,25,25,25,79,79,79,24,25,25,12,18,21,112,107,102,109,106,103,14,21,25,0,0,0,0,0,0,32,32,32,22,22,22,51,51,51,73,73,73,28,32,35,77,78,79,201,151,115,255,135,51,255,138,56,211,152,109,123,113,104,36,41,44,26,27,27,17,17,17,9,8,8,42,44,45,174,145,123,254,149,75,255,108,4,254,103,0,254,103,0,255,106,0,255,128,35,240,167,115,67,67,66,0,0,0,0,0,2,170,137,112,255,123,21,255,102,0,254,106,0,254,106,0,254,106,0,254,106,0,254,103,0,255,118,15,145,124,108,0,0,0,13,18,24,215,139,83,255,103,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,255,107,2,199,147,109,5,10,13,58,59,60,246,137,59,255,103,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,255,102,0,235,146,82,36,41,46,126,113,103,255,125,30,254,104,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,103,0,254,135,49,97,93,90,83,79,77,248,139,60,255,102,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,102,0,255,132,38,146,136,127,0,3,5,162,132,109,255,117,16,254,105,0,254,106,0,254,106,0,254,106,0,254,106,0,254,104,0,255,114,14,191,143,108,30,32,34,0,0,0,31,35,38,230,149,91,255,103,0,254,105,0,254,105,0,254,105,0,254,104,0,255,110,5,210,148,102,26,31,34,0,0,0,0,0,0,0,0,0,107,96,88,255,143,59,255,121,25,255,121,23,255,116,15,255,117,17,221,145,88,42,44,47,0,0,0,0,0,0,0,0,0,0,0,0,7,9,10,109,99,93,120,103,92,129,110,96,144,117,98,146,121,102,61,60,58,0,0,0,0,0,0,0,0,0};
const uint8_t l6[] PROGMEM = {0,0,0,25,25,25,79,79,79,24,25,25,12,18,21,112,107,102,109,106,103,14,21,25,0,0,0,0,0,0,32,32,32,22,22,22,51,51,51,73,73,73,28,32,35,77,78,79,201,151,115,255,135,51,255,138,56,211,152,109,123,113,104,36,41,44,26,27,27,17,17,17,9,8,8,42,44,45,174,145,123,254,149,75,255,108,4,254,103,0,254,103,0,255,106,0,255,128,35,240,167,115,67,67,66,0,0,0,0,0,2,170,137,112,255,123,21,255,102,0,254,106,0,254,106,0,254,106,0,254,106,0,254,103,0,255,118,15,145,124,108,0,0,0,13,18,24,215,139,83,255,103,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,255,107,2,199,147,109,5,10,13,58,59,60,246,137,59,255,103,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,255,102,0,235,146,82,36,41,46,126,113,103,255,125,30,254,104,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,103,0,254,135,49,97,93,90,83,79,77,248,139,60,255,102,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,106,0,254,102,0,255,132,38,146,136,127,0,3,5,162,132,109,255,117,16,254,105,0,254,106,0,254,106,0,254,106,0,254,106,0,254,104,0,255,114,14,191,143,108,30,32,34,0,0,0,31,35,38,230,149,91,255,103,0,254,105,0,254,105,0,254,105,0,254,104,0,255,110,5,210,148,102,26,31,34,0,0,0,0,0,0,0,0,0,107,96,88,255,143,59,255,121,25,255,121,23,255,116,15,255,117,17,221,145,88,42,44,47,0,0,0,0,0,0,0,0,0,0,0,0,7,9,10,109,99,93,120,103,92,129,110,96,144,117,98,146,121,102,61,60,58,0,0,0,0,0,0,0,0,0};

// the pins of the image selection switches (2 to the power of x)
// there is an internal Pullup Resistor, so these pins are active low!!
#define INPUT_2_0 1
#define INPUT_2_1 2
#define INPUT_2_2 3

// a global list of CRGB values per LED -> could be local?? would FastLED init have to local then?
CRGB leds[NUM_LEDS];

// a global "buffer" array for 3 rgb values per LED 
// it has to be global since its impossible to return an array (thanks to static memory allocation)
uint8_t tempList[NUM_LEDS*3];

// A global variable for the last state of the inputs
// it starts with an invaild number so that in the first loop, its never equal to input
uint8_t previousInput = 8;

void setup() { 
    FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.clear();

    Serial.begin(9600);

    pinMode(INPUT_2_0, INPUT_PULLUP);
    pinMode(INPUT_2_1, INPUT_PULLUP);
    pinMode(INPUT_2_2, INPUT_PULLUP);

}

void loop() { 

    // if serial data is available
    if(Serial.available() > 0){
        // if tempList was successfully updated, write the new list to the eeprom
        if(readSerial()){
            // write tempList to eeprom
            // debug: with tempList still in ram, write it to leds and show
            
            writeTempListToLeds();
            FastLED.show();
        }
    }

    /* disabled for serial testing
    uint8_t input = readInputs();
    // inputChanged is true if input has changed since the last loop
    bool inputChanged = previousInput != input;
    previousInput = input;

    if(inputChanged){
        updateImage(input);
    }
    */
}

bool readSerial(){ 
    // Here I hardcoded the communication "protocol" with my python program
    // to be called after if(Serial.available < 0)

    char msg = Serial.read();    
  
    // if this char is the start indicator
    if(msg == 'S'){
        Serial.print('O');


        for(int i = 0; true; i++){
            // debug Serial.println(" loop ");
            
            // the highest number can be 3 digit
            char bufferArray[3] = {'q', 'q', 'q'};
            int sizeBuffer = Serial.readBytesUntil(',', bufferArray, 6);

            // this converts ASCII to a base 10 number
            // if a number with less than 3 digits is stored in the array, there will be 'q' in the array left over from the initialisation
            // if i don't do this, a 2 would be stored as [2,0,0] and interpreted as 200
            // i don't have a better solution than testing for the length of the number

            int thisValue = 0;
            if(bufferArray[0]=='q' && bufferArray[1]=='q' && bufferArray[2]=='q'){ // 0 digits
                // if this occurs, then there was a problem with the serial communication, thus return false
                return false;
            }
            if(bufferArray[0]!='q' && bufferArray[1]=='q' && bufferArray[2]=='q'){ // 1 digit
                thisValue = (bufferArray[0] & 0xf);
            }
            if(bufferArray[0]!='q' && bufferArray[1]!='q' && bufferArray[2]=='q'){ // 2 digits
                thisValue = (bufferArray[0] & 0xf) *10;
                thisValue += (bufferArray[1] & 0xf);
            }
            if(bufferArray[0]!='q' && bufferArray[1]!='q' && bufferArray[2]!='q'){ // 3 digits
                thisValue = (bufferArray[0] & 0xf) *100;
                thisValue += (bufferArray[1] & 0xf) *10;
                thisValue += (bufferArray[2] & 0xf);
            }
            

            // assign the read value to the buffer
            tempList[i] = thisValue;
            
            // if the end char is detected, the loop is terminated and the vaild list is returned
            // this is peek() in order to not erase the next value from the serial buffer
            char endMsg = Serial.peek();
            if(endMsg == 'E'){
                // debug Serial.println(" end of loop ");
                
                return true;
            }
            // if the loop runs for longer than expected, the loop is terminated and false is returned
            if(i > NUM_LEDS*3 + 10){
                // debug Serial.println(" loop timeout ");
                
                return false;
            }
        }
    }
    return false;
}

int readInputs(){

    // digitalRead returns 0 for LOW and 1 for HIGH
    uint8_t in0 = digitalRead(INPUT_2_0);
    uint8_t in1 = digitalRead(INPUT_2_1);
    uint8_t in2 = digitalRead(INPUT_2_2);

    // to convert this "binary number" into base then, multiply each bit by the corresponding power of 2
    uint8_t input = in0 * 1 + in1 * 2 + in2 * 4 ; 
    
    // for debug
    input = 5;
    return input;
}

bool getHardcodedList(uint8_t number){
    // number has to be between 0 and 6

    switch(number){
        case 0:
            for(int i = 0; i < NUM_LEDS*3; i++){
                tempList[i] = pgm_read_byte(&l0[i]);
            }
            break;
        case 1:
            for(int i = 0; i < NUM_LEDS*3; i++){
                tempList[i] = pgm_read_byte(&l1[i]);
            }
            break;
        case 2:
            for(int i = 0; i < NUM_LEDS*3; i++){
                tempList[i] = pgm_read_byte(&l2[i]);
            }
            break;
        case 3:
            for(int i = 0; i < NUM_LEDS*3; i++){
                tempList[i] = pgm_read_byte(&l3[i]);
            }
            break;
        case 4:
            for(int i = 0; i < NUM_LEDS*3; i++){
                tempList[i] = pgm_read_byte(&l4[i]);
            }
            break;
        case 5:
            for(int i = 0; i < NUM_LEDS*3; i++){
                tempList[i] = pgm_read_byte(&l5[i]);
            }
            break;
        case 6:
            for(int i = 0; i < NUM_LEDS*3; i++){
                tempList[i] = pgm_read_byte(&l6[i]);
            }
            break;
        default:
            return false;
    }
    
    return true; 
}

void writeTempListToLeds(){ 
    // The for loop is executed once for every pixel, and the R,G and B values of the pixel are written to the corresponding LED 
    // in the leds array by having a simultaneous counter that increments in steps of 1 instead of 3 (as i3)

    int i = 0;
    for(int i3 = 0; i3 < NUM_LEDS*3; i3 += 3){
      
        // This might have to be adjusted this if the colors seem wrong
        uint8_t R = tempList[i3];
        uint8_t G = tempList[i3 + 1];
        uint8_t B = tempList[i3 + 2];

        leds[i].setRGB(R, G, B);

        i++;
    }
}

void updateImage(uint8_t input){

    // input 7 is the image via Serial
    if(input == 7){
        // read list from eeprom into tempList
    }
    // input 0 to 6 are the hardcoded images
    if(input >= 0 && input <= 6){
        // get one of the hardcoded lists
        getHardcodedList(input);
    }else{
        // input is invalid, terminate the function
        return;
    }

    // then write the updated tempList to leds and show
    writeTempListToLeds();
    Serial.println(" leds is shown ");
    FastLED.show();
}
