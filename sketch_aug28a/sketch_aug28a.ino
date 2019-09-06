
#define BDD D7
#define LED D6// choose input pin (for Infrared sensor) 
int val = 0; // variable for reading the pin status 
void setup() 
{ 
  Serial.begin(9600);
   pinMode(BDD, INPUT);
     pinMode(LED, OUTPUT);// declare Infrared sensor as input
} 
void loop()
{ 
   val = digitalRead(BDD); // read input value 
   if (val == 1)
   { // check if the input is HIGH
      Serial.println("Object is far away"); // turn LED OFF  
      digitalWrite(LED,HIGH); 
   } 
   else 
   { 
      Serial.println("Caution caution Caution!!!");
      digitalWrite(LED,LOW);
   } 
   delay(500);
}
