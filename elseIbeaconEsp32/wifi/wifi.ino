#include <WiFi.h>
#include "FirebaseESP32.h"
#include "time.h"
String time_str;
#define FIREBASE_HOST "https://elseconsumerdatabase.firebaseio.com/" //Change to your Firebase RTDB project ID e.g. Your_Project_ID.firebaseio.com
#define FIREBASE_AUTH "HqBLu0LN9OMx7AcjiI6YeJaZNdPP8XUD0aY0RYMb"  //Change to your Firebase RTDB secret password
#define WIFI_SSID "375"
#define WIFI_PASSWORD "Whitepepper"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800;
const int   daylightOffset_sec = 3600;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  printLocalTime();
  delay(2000);
}

void printLocalTime(){
  //struct tm timeinfo;
  //if(!getLocalTime(&timeinfo)){
   // Serial.println("Failed to obtain time");
    //return;
  //}
  //Serial.println(&timeinfo, "%B %d %Y %H:%M:%S");
    time_t seconds; 
      
    seconds = time(NULL); 
    Serial.printf("Seconds since January 1, 1970 = %ld\n", seconds); 
}
