#include <WiFi.h>
#include "FirebaseESP32.h"
#include "sys/time.h"
#include "BLEDevice.h"
#include "BLEUtils.h"
#include "BLEBeacon.h"
#include "esp_sleep.h"

#define FIREBASE_HOST "https://elseconsumerdatabase.firebaseio.com/" //Change to your Firebase RTDB project ID e.g. Your_Project_ID.firebaseio.com
#define FIREBASE_AUTH "HqBLu0LN9OMx7AcjiI6YeJaZNdPP8XUD0aY0RYMb" //Change to your Firebase RTDB secret password

#define GPIO_DEEP_SLEEP_DURATION     1  // sleep x seconds and then wake up
RTC_DATA_ATTR static time_t last;        // remember last boot in RTC Memory
RTC_DATA_ATTR static uint32_t bootcount; // remember number of boots in RTC Memory

#ifdef __cplusplus
extern "C" {
#endif

uint8_t temprature_sens_read();
//uint8_t g_phyFuns;

#ifdef __cplusplus
}
#endif

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
BLEAdvertising *pAdvertising;
struct timeval now;

#define BEACON_UUID           "00000000-0000-0000-0000-000000000000" // UUID 1 128-Bit (may use linux tool uuidgen or random numbers via https://www.uuidgenerator.net/)
const char* ssid = "375";
const char* password = "Whitepepper";
void setBeacon() {

  BLEBeacon oBeacon = BLEBeacon();
  oBeacon.setManufacturerId(0x4C00); // fake Apple 0x004C LSB (ENDIAN_CHANGE_U16!)
  oBeacon.setProximityUUID(BLEUUID(BEACON_UUID));
  oBeacon.setMajor((bootcount & 0xFFFF0000) >> 16);
  oBeacon.setMinor(bootcount&0xFFFF);
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

void setup() {

    
  Serial.begin(115200);
  gettimeofday(&now, NULL);
 
  //Serial.printf("deep sleep (%lds since last reset, %lds since last boot)\n",now.tv_sec,now.tv_sec-last);

  last = now.tv_sec;
  
  // Create the BLE Device
  BLEDevice::init("Else");

  // Create the BLE Server
  // BLEServer *pServer = BLEDevice::createServer(); // <-- no longer required to instantiate BLEServer, less flash and ram usage

  pAdvertising = BLEDevice::getAdvertising();
  
  setBeacon();
   // Start advertising
  pAdvertising->start();
  Serial.println("Advertizing started...");

 
  
  //delay(100);
  //pAdvertising->stop();
  //Serial.printf("enter deep sleep\n");
  //esp_deep_sleep(1000000LL * GPIO_DEEP_SLEEP_DURATION);
  //Serial.printf("in deep sleep\n");
}

void loop() {
}
