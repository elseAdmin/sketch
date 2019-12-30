#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"
#define FIREBASE_HOST "https://elseconsumerdatabase.firebaseio.com/"
#define FIREBASE_OAUTH "HqBLu0LN9OMx7AcjiI6YeJaZNdPP8XUD0aY0RYMb"

// defines variables
const char *ssid =  "375";     // replace with your wifi ssid and wpa2 key
const char *pass =  "Whitepepper";
const int trigPin = 5;    // pin no. 5 is D1 ESP8266
const int echoPin = 4;    // pin no. 4 is D2 ESP8266

long duration;
int dist;
WiFiClient client;
int val = 0;
FirebaseData firebaseData;

void printJsonObjectContent(FirebaseData &data); //mandatory method

void setup()
{
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to internet.");
  Firebase.begin(FIREBASE_HOST, FIREBASE_OAUTH);
  Firebase.reconnectWiFi(true);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
}
void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  dist = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println("cms");

  if (dist < 200) {
   //if <200cm we consider that there is a car parked
    Firebase.begin(FIREBASE_HOST, FIREBASE_OAUTH);
    Firebase.reconnectWiFi(true);
    Firebase.setInt(firebaseData, "unityOneRohini/parking/sensor2/value", 1);
  } else {
    Firebase.begin(FIREBASE_HOST, FIREBASE_OAUTH);
    Firebase.reconnectWiFi(true);
    Firebase.setInt(firebaseData, "unityOneRohini/parking/sensor2/value", 0);
  }
}
