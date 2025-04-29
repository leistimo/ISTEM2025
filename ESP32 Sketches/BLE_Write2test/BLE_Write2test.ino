/*  11.020 - Simple BLE server

   This example sketch shows how to create a BLE service with two read/write characteristics.

   After you upload the sketch to your ESP32, use a BLE app, such as BLE Scanner, to interact with 
   the BLE service running on the ESP32.

   This sketch was written by Peter Dalmaris using information from the
   ESP32 datasheet and examples.


   Components
   ----------
    - ESP32 Dev Kit v4


    IDE
    ---
    Arduino IDE with ESP32 Arduino Code
    (https://github.com/espressif/arduino-esp32)


    Libraries
    ---------
    - BLEDevice
    - BLEUtils
    - BLEServer

   Connections
   -----------

   No external hardware needed.


    Other information
    -----------------

    1. ESP32 Datasheet: https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf
    2. BLE Scanner app on Google Play (you may need to search for this in your store): https://play.google.com/store/apps/details?id=com.macdom.ble.blescanner&hl=en_AU
    3. BLE Scanner app on iTunes (you may need to search for this in your store): https://itunes.apple.com/au/app/ble-scanner-4-0/id1221763603?mt=8
    4. GATT overview: https://www.bluetooth.com/specifications/gatt/generic-attributes-overview
    5. UUID generator: https://www.uuidgenerator.net
    6. GATT Characteristics: https://www.bluetooth.com/specifications/gatt/characteristics
    7. Learn more about std::string --> https://en.wikipedia.org/wiki/C%2B%2B_string_handling

    Created on April 9 2019 by Peter Dalmaris

*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID         "ce3fa4b9-9d6d-4787-963f-2afab5cc061e"  // This is a custom service
#define CHARACTERISTIC_UUID1 "32e97b51-92d1-4911-94f9-833213e35892"  // This is a custom characteristic
#define CHARACTERISTIC_UUID2 "9035bf14-6416-4b6e-9a74-fcd74682e4e1"  // This is a custom characteristic


class MyCallbacks1: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      //std::string value = pCharacteristic->getValue();
      String value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New value Char 1: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};

class MyCallbacks2: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      //std::string value = pCharacteristic->getValue();
      String value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New value Char 2: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("TimL_is_Cool_BLE");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic1 = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID1,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
                                       
  BLECharacteristic *pCharacteristic2 = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID2,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic1->setCallbacks(new MyCallbacks1());

  pCharacteristic1->setValue("Hello World char 1");

  pCharacteristic2->setCallbacks(new MyCallbacks2());

  pCharacteristic2->setValue("Hello World char 2");
  
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  
  pAdvertising->start();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}