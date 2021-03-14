
//Classes have to be defined BEFORE they are called!
class ClassTest{
  public:
    int testInt;
    String testString;

    // take two Strings and add them up to one String
    String addChars(String someString, String toBeAdded){
      someString = someString + toBeAdded;
      return someString;
    }
};

void setup() {
  Serial.begin(9600);

  // create an instance of the class ClassTest called myObject
  ClassTest myObject;

  myObject.testInt = 10;
  Serial.println(myObject.testInt);

  myObject.testString = "TO THE MOON AND BEYOND ";
  Serial.println(myObject.testString);

  myObject.testString = myObject.addChars(myObject.testString, "+++");
  Serial.println(myObject.testString);
}

void loop() {
  
}
