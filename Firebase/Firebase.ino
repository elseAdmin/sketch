#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"

#define IRSENSOR D7
#define LED D6
#define FIREBASE_HOST "https://parkingdata-b7617.firebaseio.com/"
#define FIREBASE_OAUTH "tgD4NjyoqkOdACT0x473u7O1hhWXUCoKiWTY0tZr"

const char *ssid =  "375";     // replace with your wifi ssid and wpa2 key
const char *pass =  "Whitepepper";

WiFiClient client;
int val = 0;
FirebaseData firebaseData;
void printJsonObjectContent(FirebaseData &data);

void setup()
{
  Serial.begin(9600);
  //pinMode(IRSENSOR, INPUT);
  // pinMode(LED, OUTPUT);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to internet.");
  Firebase.begin(FIREBASE_HOST, FIREBASE_OAUTH);
  Firebase.reconnectWiFi(true);
Firebase.setString(firebaseData,"Rishab", "Gandu"); 
}


void loop()
{
   
  /*
    val = digitalRead(IRSENSOR);
    if (val == 1)
    { // check if the input is HIGH
      Serial.println("Object is far away");
      digitalWrite(LED,HIGH);
    }
    else
    {
      Serial.println("Caution caution Caution!!!");
      digitalWrite(LED,LOW);
    }
    delay(500);
  */
}
