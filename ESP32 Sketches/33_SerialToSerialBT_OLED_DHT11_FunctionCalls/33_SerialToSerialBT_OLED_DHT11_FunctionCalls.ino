// This example code is in the Public Domain (or CC0 licensed, at your option.)
// By Evandro Copercini - 2018
//
// This example creates a bridge between Serial and Classical Bluetooth (SPP)
// and also demonstrate that SerialBT have the same functionalities of a normal Serial
// Note: Pairing is authenticated automatically by this device


#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 32  // ESP32 Dev. Board V1 note: Do not use GPIO 34, 35, 36, or 39 
#define DHTTYPE    DHT11     // DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

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

String SerialReadBT;

void setup() {
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  
  delayMS = sensor.min_delay / 1000;// Set delay between sensor readings based on sensor details.

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

int Temperature;
int Humidity;

void DisplaySetup(){
  display.clearDisplay();
  display.setTextSize(2);
  //display.setTextColor(WHITE);
  display.setRotation(0);
  display.setCursor(0, 10);
}
void RecievedSMdata(){
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

void RecievedBTdata(){
  SerialReadBT = (SerialBT.readString());
    delay(200);
    display.print("BT: ");
    display.print(SerialReadBT);//loading data prior to display
    display.display();             //Update the OLED display 

    Serial.print("BT: ");
    for(int i=0; i<SerialReadBT.length(); i++) {
    Serial.write(SerialReadBT.charAt(i));
      }
}
void RGB(){
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
void TempHumid(){
  if(SerialReadBT.charAt(1)=='T'){
        SendTemperature();
      }
      
  if(SerialReadBT.charAt(2)=='H'){
        SendHumidity();
      } 
}
void SendTemperature(){
        SerialBT.print("Temperature = ");
        SerialBT.print(Temperature);
        SerialBT.println(F("°C"));
        Serial.print(F("Temperature: "));
        Serial.print(Temperature);
        Serial.println(F("°C"));
        }
void SendHumidity() {
        SerialBT.print("Humidity = ");
        SerialBT.print(Humidity);
        SerialBT.println(F("%"));
        Serial.print(F("Humidity: "));
        Serial.print(Humidity);
        Serial.println(F("%"));
        }


void loop() {

  delay(delayMS);// Delay between measurements.
  
  sensors_event_t event;// Get temperature event and print its value.
  dht.temperature().getEvent(&event);

  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Temperature = (event.temperature);
  }
  
  dht.humidity().getEvent(&event); // Get humidity event and print its value.
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Humidity = (event.relative_humidity);
  }
  
  DisplaySetup();
  
  if (Serial.available()) {
    RecievedSMdata();//Recieve data from the serial monitor and update OLED
  }

  if (SerialBT.available()) {
    RecievedBTdata();//Recieve data from bluetooth (phone) and update OLED & Serial Monitor

    if (SerialReadBT.charAt(0)=='$'){
      RGB();
    }

    if (SerialReadBT.charAt(0)=='%'){
      TempHumid();
    }
  } 
}
