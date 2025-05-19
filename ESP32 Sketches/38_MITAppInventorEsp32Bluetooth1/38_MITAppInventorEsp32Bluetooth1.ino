//ESP32 Dev Module
#include <Arduino.h>
        #include <BluetoothSerial.h>

        BluetoothSerial SerialBT;
        #define Onboard_Blue 2
        #define Top_Red 13

        void setup() {
          SerialBT.begin("ESP32test"); // Name of your ESP32 device
          Serial.begin(115200);
          pinMode(Onboard_Blue, OUTPUT);
          digitalWrite(Onboard_Blue, LOW);
        }

        void loop() {
          if (SerialBT.available()) {
            String receivedData = SerialBT.readStringUntil('\n'); // Read until newline
            Serial.print("Received: ");
            Serial.println(receivedData);
            SerialBT.print("Data received");
            if(receivedData == "1"){
              digitalWrite(Onboard_Blue, HIGH);
            }
              else if(receivedData == "0"){
              digitalWrite(Onboard_Blue, LOW);
             }
              
          }
        }
