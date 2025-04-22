// This example code is in the Public Domain (or CC0 licensed, at your option.)
// By Evandro Copercini - 2018
//
// This example creates a bridge between Serial and Classical Bluetooth (SPP)
// and also demonstrate that SerialBT have the same functionalities of a normal Serial
// Note: Pairing is authenticated automatically by this device

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels

#define LED_Green 13 //Add Variable LED_External and assign it to GPIO13
#define LED_Red 14
#define LED_Blue 12

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

String SerialRead;
//char *SerialRead[15];
String SerialReadBT;

void setup() {
  pinMode(LED_Red, OUTPUT);   // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_Green, OUTPUT);  // initialize digital pin LED_External as an output.
  pinMode(LED_Blue, OUTPUT);  // initialize digital pin LED_External as an output.

  digitalWrite(LED_Red, LOW);   // initialize low or off. 
  digitalWrite(LED_Blue, LOW);  // initialize low or off.
  digitalWrite(LED_Green, LOW);

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

  display.println("Waiting for Message");//loading data prior to display
  display.display();             //Update the OLED display 
}

void loop() {

  display.clearDisplay();
  display.setTextSize(2);
  //display.setTextColor(WHITE);
  display.setRotation(0);
  display.setCursor(0, 10);

  if (Serial.available()) {
    SerialRead = Serial.readString();
    
    delay(200);
    display.print("SM: "); 
    display.print(SerialRead);//loading data prior to display
    display.display();             //Update the OLED display 
    
    for(int i=0; i<SerialRead.length(); i++) {
    SerialBT.write(SerialRead.charAt(i));
      }

    Serial.print("SM: ");
    for(int i=0; i<SerialRead.length(); i++) {
    Serial.write(SerialRead.charAt(i));
      }
  }

  if (SerialBT.available()) {
    SerialReadBT = (SerialBT.readString());
    
    delay(200);
    display.print("BT: ");
    display.print(SerialReadBT);//loading data prior to display
    display.display();             //Update the OLED display 

    Serial.print("BT: ");
    for(int i=0; i<SerialReadBT.length(); i++) {
    Serial.write(SerialReadBT.charAt(i));
      }
    
    if (SerialReadBT.charAt(0)=='$'){
      if(SerialReadBT.charAt(1)=='R'){
        digitalWrite(LED_Red, HIGH);
        SerialBT.println("Red LED on");
      }
      else {
        digitalWrite(LED_Red, LOW);
      } 

      if(SerialReadBT.charAt(2)=='G'){
        digitalWrite(LED_Green, HIGH);
        SerialBT.println("Green LED on");
      } 
      else {
        digitalWrite(LED_Green, LOW);
      } 
      
      if(SerialReadBT.charAt(3)=='B'){
        digitalWrite(LED_Blue, HIGH);
        SerialBT.println("Blue LED on");
      } 
      else {
        digitalWrite(LED_Blue, LOW);
      }   
    }

  }
   
}
