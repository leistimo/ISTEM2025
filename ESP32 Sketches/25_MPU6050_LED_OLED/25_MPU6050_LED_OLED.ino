#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

#include <Adafruit_MPU6050.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

// pins for the LEDs:
const byte LED_Red = 14;  
const byte LED_Blue = 12;
const byte LED_Green = 13;

Adafruit_MPU6050 mpu;

void setup() {
  // initialize serial:
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

   // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

   mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);

  // make the pins outputs:
  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Blue, OUTPUT);
  pinMode(LED_Green, OUTPUT);

  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Blue, LOW);
  digitalWrite(LED_Red, LOW);

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

}
 
void loop() {
  
   /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("AccelX:");
  Serial.print(a.acceleration.x);
  
  if (a.acceleration.x > 1){
    digitalWrite(LED_Red, HIGH);
    display.print("Bank Right = ");
    display.println(a.acceleration.x);//loading data prior to display
  }
  
  else  {
    digitalWrite(LED_Red, LOW);
  }

  if (a.acceleration.x <-1){
    digitalWrite(LED_Green, HIGH);
    display.print("Bank Left = ");
    display.println(a.acceleration.x);//loading data prior to display
  }

  else  {
    digitalWrite(LED_Green, LOW);
  }

  if (a.acceleration.x < 1 && a.acceleration.x >-1 ){
    display.println("Straight");
  }

  Serial.print(",");
  Serial.print("AccelY:");
  Serial.print(a.acceleration.y);

  if (a.acceleration.y > 1 || a.acceleration.y <-1 ){
    digitalWrite(LED_Blue, HIGH);
    if(a.acceleration.y > 1){
      display.print("Nose Down = ");
      display.println(a.acceleration.y);//loading data prior to display
    }
    if(a.acceleration.y < 1){
      display.print("Nose Up = ");
      display.println(a.acceleration.y);//loading data prior to display
    }
    
  }
  
  else  {
    digitalWrite(LED_Blue, LOW);
    display.println("Level");
    
  }

  
  Serial.print(",");
  Serial.print("AccelZ:");
  Serial.print(a.acceleration.z);
  Serial.print(", ");
  Serial.print("GyroX:");
  Serial.print(g.gyro.x);
  Serial.print(",");
  Serial.print("GyroY:");
  Serial.print(g.gyro.y);
  Serial.print(",");
  Serial.print("GyroZ:");
  Serial.print(g.gyro.z);
  Serial.println("");

  delay(10);
  display.display(); 
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);
  display.setCursor(0, 0);
}
  
  