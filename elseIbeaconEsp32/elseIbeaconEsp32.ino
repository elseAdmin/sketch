#include <WiFi.h>
#include "FirebaseESP32.h"
#include "BLEDevice.h"
#include "BLEUtils.h"
#include "BLEBeacon.h"
#include "time.h"

#define FIREBASE_HOST "https://elseconsumerdatabase.firebaseio.com/" //Change to your Firebase RTDB project ID e.g. Your_Project_ID.firebaseio.com
#define FIREBASE_AUTH "HqBLu0LN9OMx7AcjiI6YeJaZNdPP8XUD0aY0RYMb" //Change to your Firebase RTDB secret password
#define WIFI_SSID "375"
#define WIFI_PASSWORD "Whitepepper"
const int trigPin = 2;
const int echoPin = 5;
bool isCar = false;
FirebaseData firebaseData;
long duration;
int dist;
time_t secondsSinceEpoch;

#ifdef __cplusplus
extern "C" {
#endif

uint8_t temprature_sens_read();
//uint8_t g_phyFuns;

#ifdef __cplusplus
}
#endif

BLEAdvertising *pAdvertising;
#define BEACON_UUID  "00000000-0000-0000-0000-000000000000"

void setBeacon() {
  BLEBeacon oBeacon = BLEBeacon();
  oBeacon.setManufacturerId(0x4C00); // fake Apple 0x004C LSB (ENDIAN_CHANGE_U16!)
  oBeacon.setProximityUUID(BLEUUID(BEACON_UUID));
  oBeacon.setMajor((0 & 0xFFFF0000) >> 16);
  oBeacon.setMinor(0 & 0xFFFF);
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
  BLEAdvertisementData oScanResponseData = BLEAdvertisementData();

  oAdvertisementData.setFlags(0x04); // BR_EDR_NOT_SUPPORTED 0x04

  std::string strServiceData = "";

  strServiceData += (char)26;     // Len
  strServiceData += (char)0xFF;   // Type
  strServiceData += oBeacon.getData();
  oAdvertisementData.addData(strServiceData);

  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->setScanResponseData(oScanResponseData);
}

void getCurrentMillis() {
  secondsSinceEpoch = time(NULL);
  Serial.println(secondsSinceEpoch);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println("WiFi Connected. ");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  BLEDevice::init("Else");
  pAdvertising = BLEDevice::getAdvertising();
  setBeacon();
  pAdvertising->start();
  Serial.println("Advertizing BLE started...");
  configTime(19800, 3600, "pool.ntp.org");
  secondsSinceEpoch = time(NULL);
  Serial.println(secondsSinceEpoch);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist = duration * 0.034 / 2;

  if (dist < 30 && !isCar) {
    Serial.println("detected a vehicle, updating firebase");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
    getCurrentMillis();
    Firebase.setInt(firebaseData, "unityOneRohini/parking/sensor5/updatedAt", secondsSinceEpoch);
    Firebase.setInt(firebaseData, "unityOneRohini/parking/sensor5/value", 1);
    isCar = true;
  } else if (dist >= 30 && isCar) {
    Serial.println("no vehicle detected, updating firebase");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
    getCurrentMillis();
    Firebase.setInt(firebaseData, "unityOneRohini/parking/sensor5/updatedAt", secondsSinceEpoch);
    Firebase.setInt(firebaseData, "unityOneRohini/parking/sensor5/value", 0);
    isCar = false;
  }
}
