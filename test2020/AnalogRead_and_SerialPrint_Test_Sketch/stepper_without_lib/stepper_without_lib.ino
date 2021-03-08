int Pin0 = 10; 
int Pin1 = 11; 
int Pin2 = 12; 
int Pin3 = 13; 
int _step = 0; 
int num = 0;

void setup() 
{ 
 pinMode(Pin0, OUTPUT);  
 pinMode(Pin1, OUTPUT);  
 pinMode(Pin2, OUTPUT);  
 pinMode(Pin3, OUTPUT);  

 Serial.begin(9600);
} 
 void loop() 
{ 
Serial.write(num);

if (num == 1)
{
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, HIGH); 
}
else if (num == 2)
{
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, HIGH); 
     digitalWrite(Pin3, HIGH); 
}
else if (num == 3)
{
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, HIGH); 
     digitalWrite(Pin3, LOW); 
}
else if (num == 4)
{
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, HIGH); 
     digitalWrite(Pin2, HIGH); 
     digitalWrite(Pin3, LOW); 
}
else if (num == 5)
{
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, HIGH); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
}
else if (num == 6)
{
     digitalWrite(Pin0, HIGH);  
     digitalWrite(Pin1, HIGH); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
}
else if (num == 7)
{
     digitalWrite(Pin0, HIGH);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
}
else if (num == 8)
{
     digitalWrite(Pin0, HIGH);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, HIGH); 
}
else if (num == 9)
{
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
}
else {}

delay(500);
num = num + 1 ;
}
