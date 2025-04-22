// This example code is in the Public Domain (or CC0 licensed, at your option.)
// By Evandro Copercini - 2018
//
// This example creates a bridge between Serial and Classical Bluetooth (SPP)
// and also demonstrate that SerialBT have the same functionalities of a normal Serial
// Note: Pairing is authenticated automatically by this device

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

#define MAX_MESSAGE 30
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);


#include "BluetoothSerial.h"

String device_name = "TimL-is-Cool";

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name);  //Bluetooth device name
  //SerialBT.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());

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

  display.println("Message: Hello World");//loading data prior to display
  display.display();             //Update the OLED display 
}

void loop() {

static char buffer[MAX_MESSAGE];
  static unsigned char index = 0;
  char inch;
  
  while (Serial.available() > 0) {
    inch = Serial.read();
    if (inch == '\r') {
      Serial.print("You entered: ");
      Serial.println(buffer);
      buffer[0] = 0;
      index = 0;
    } else {        
      if (index < MAX_MESSAGE-1) {
        buffer[index++] = inch;
        buffer[index] = 0;
      }
    }
  } 
}

  //display.clearDisplay();
  //display.setTextSize(1);
  //display.setTextColor(WHITE);
  //display.setRotation(0);
  //display.setCursor(0, 0);

  if (Serial.available()) {
    
    char SerialRead = (Serial.readstring());
     delay(200);
    display.print("SM: "); 
    display.print(SerialRead);//loading data prior to display
    display.display();             //Update the OLED display 
    SerialBT.write(SerialRead);
  }
  //if (SerialBT.available()) {
   // Serial.write(SerialBT.read());
   // display.print("Phone: ");
   // display.print(SerialBT.read());//loading data prior to display
   // display.display();             //Update the OLED display
  //}
   
  delay(200);
}
