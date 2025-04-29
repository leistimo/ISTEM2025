/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleWrite.cpp
    Ported to Arduino ESP32 by Evandro Copercini
*/

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);


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

        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("MSG1:");
        display.println(value);
        display.display();  // Display AdaFruit Logo
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
        
        //delay(2000);        // Pause for 2 seconds
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("MSG2:");
        display.println(value);
        display.display();  // Display AdaFruit Logo
        //display.setTextSize(1);
        //display.setTextColor(WHITE);
        //display.setRotation(0);
        
      }
    }
};

void setup() {
  Serial.begin(115200);

  Wire.begin();  // Initialize I2C communication
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  display.display();  // Display AdaFruit Logo
  delay(2000);        // Pause for 2 seconds
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);
  display.setCursor(0, 0);

  display.println("Waiting for Message");//loading data prior to display
  display.display();             //Update the OLED display 


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
