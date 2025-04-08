#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

// pins for the LEDs:
const int redPin = 14;
const int greenPin = 13;
const int bluePin = 12;

void setup() {
  // initialize serial:
  Serial.begin(115200);
  // make the pins outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

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

  display.println("Message: Enter Values");//loading data prior to display
  display.display();             //Update the OLED display 
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int red = Serial.parseInt();
    // do it again:
    int green = Serial.parseInt();
    // do it again:
    int blue = Serial.parseInt();

    // look for the newline. That's the end of your sentence:
    if (Serial.read() == '\n') {
      // constrain the values to 0 - 255 and invert
      // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
     // red = 255 - constrain(red, 0, 255);
    //  green = 255 - constrain(green, 0, 255);
    //  blue = 255 - constrain(blue, 0, 255);

      red = constrain(red, 0, 255);
      green = constrain(green, 0, 255);
      blue = constrain(blue, 0, 255);

      // fade the red, green, and blue legs of the LED:
      analogWrite(redPin, red);
      analogWrite(greenPin, green);
      analogWrite(bluePin, blue);

      // print the three numbers in one string as hexadecimal:
      Serial.print("red=");
      Serial.print(red, HEX);
      Serial.print(" ");
      Serial.print("green=");
      Serial.print(green, HEX);
      Serial.print(" ");
      Serial.print("blue=");      
      Serial.println(blue, HEX);

    //  display.display();  // Display AdaFruit Logo
    //delay(2000);        // Pause for 2 seconds
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setRotation(0);
    display.setCursor(0, 0);

    display.print("red = ");
    display.println(red, HEX);//loading data prior to display

    display.print("green = ");
    display.println(green, HEX);//loading data prior to display

    display.print("blue = ");
    display.println(blue, HEX);//loading data prior to display

    display.display();             //Update the OLED display 
      
    }
  }
}
