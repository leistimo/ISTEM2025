/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleWrite.cpp
    Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "f573d4c5-3364-486a-a383-a0fcf0e119fc"
#define CHARACTERISTIC_UUID1 "d35026d6-9f99-42ee-81a6-49039fe1af49"
#define CHARACTERISTIC_UUID2 "f990b3cd-dfdb-4fce-94e9-935176b6f507" 

class MyCallbacks1 : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String value = pCharacteristic->getValue();

    if (value.length() > 0) {
      Serial.println("*********");
      Serial.print("Value1: ");
      for (int i = 0; i < value.length(); i++) {
        Serial.print(value[i]);
      }

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
        Serial.print("Value2: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("TSL_ESP32");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic1 = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID1,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  
  BLECharacteristic *pCharacteristic2 =pService->createCharacteristic(
                                        CHARACTERISTIC_UUID2, 
                                        BLECharacteristic::PROPERTY_READ |
                                        BLECharacteristic::PROPERTY_WRITE
                                        );

  //pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic1->setCallbacks(new MyCallbacks1());

  pCharacteristic1->setValue("Hello World 1");

  pCharacteristic2->setCallbacks(new MyCallbacks2());

  pCharacteristic2->setValue("Hello World 2");

  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  Serial.println("1- Download and install an BLE scanner app in your phone");
  Serial.println("2- Scan for BLE devices in the app");
  Serial.println("3- Connect to MyESP32");
  Serial.println("4- Go to CUSTOM CHARACTERISTIC in CUSTOM SERVICE and write something");
  Serial.println("5- See the magic =)");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}
