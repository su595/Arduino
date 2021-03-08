
//EncoderRed und White haben Pull Down Wiederstand

boolean ReadEncoderRed = false;
boolean ReadEncoderWhite = false;
int EncoderRed = 1; //noch festlegen
int EncoderWhite = 2; //noch festlegen
int Position = 0;  

void setup() {

  Serial.begin(9600);

}

void loop() {
  
  do{
    delay(1); //Delay muss kleiner sein als DeltaT von Red und White (siehe OneNote)
    ReadEncoderRed = digitalRead(EncoderRed);
    ReadEncoderWhite = digitalRead(EncoderWhite);

    } while(!ReadEncoderRed && !ReadEncoderWhite);
    
  if(ReadEncoderRed){ //EncoderRed wird nicht erneut ausgelesen, also ist das der Wert von der Schleife oben
    Position++;
    }
  if(ReadEncoderWhite) {
    Position--;
    }
  if(Position == -1){
    Position = 23;
    }
  Serial.print(Position);
  
}
