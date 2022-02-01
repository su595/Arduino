
//Fertig!! Yay

const int sense = 2; //Pullup resistor to vcc, connected to lid, main body grounded. When closed lid and body are connected
const int speaker = 3; //Regular small speaker
const int hidden = 4; //Some kind of input (i.e button) that when activated is high

boolean firstpress = false;

void setup() {
  pinMode(sense, INPUT);
  pinMode(speaker, OUTPUT);
  pinMode(hidden, INPUT);
  Serial.begin(9600);
}

void loop() {

  if(digitalRead(sense) == 1){
    if(firstpress == true){
      analogWrite(speaker, 40); delay(300); analogWrite(speaker, 0);
      delay(100);
      analogWrite(speaker, 40); delay(100); analogWrite(speaker, 0);
      Serial.print("Bitte öffnen");
      while(digitalRead(sense) == 1){} //Damit piepen nur einmal passiert
    }
    else{
      analogWrite(speaker, 200);
      Serial.print("Alarm an");
      delay(3000);
      analogWrite(speaker, 0);
    }
  }


  if(firstpress == false){
    
   if(digitalRead(hidden) == 1){   //Hidden ist die Input-Methode. Zuerst hidden an, wenn nach 300mil aus, muss hidden innerhalb 1000mil einmal angehen, dann firstpress true.(Damit wenn hidden permanent gedrückt wird, firstpress nicht true)
    delay(300);
    if(digitalRead(hidden) == 0){
    
      for(int a=0; a<1000; a++){
        if(digitalRead(hidden) == 1) firstpress = true;
        
      delay(1);
      }
    }   
   }
  }
  else if(firstpress == true){ //else IF ist unnötig aber egal
    if(digitalRead(hidden) == 1){
      firstpress = false;

      analogWrite(speaker, 40);
      delay(300);
      analogWrite(speaker, 0);
      
      Serial.print("Reset");
      while(digitalRead(hidden) == 1){}
    }
  }


  
  if(firstpress == true) Serial.print("firstpress true"); //Debugging
  else if(firstpress == false) Serial.print("firstpress false  ");
  
  Serial.print(digitalRead(sense));
  Serial.println();
  delay(100);
}
