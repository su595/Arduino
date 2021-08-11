void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  char filepath[5] = "ligs/";
  char buffer1[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', '\0'};
  char buffer2[] = ".txt";

  Serial.println(filepath);
  Serial.println(buffer1);
  Serial.println(buffer2);
  
  strcat(filepath, buffer1);
  strcat(filepath, buffer2);

  Serial.println(filepath);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
