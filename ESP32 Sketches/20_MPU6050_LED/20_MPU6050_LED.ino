// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

const byte LED_Red = 14;  
const byte LED_Blue = 12;
const byte LED_Green = 13;

Adafruit_MPU6050 mpu;

void setup(void) {
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

  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Blue, OUTPUT);
  pinMode(LED_Green, OUTPUT);

  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Blue, LOW);
  digitalWrite(LED_Red, LOW);
}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("AccelX:");
  Serial.print(a.acceleration.x);
  
  if (a.acceleration.x > 2){
    digitalWrite(LED_Red, HIGH);
  }
  
  else  {
    digitalWrite(LED_Red, LOW);
  }

  if (a.acceleration.x <-2){
    digitalWrite(LED_Green, HIGH);
  }

  else  {
    digitalWrite(LED_Green, LOW);
  }
  Serial.print(",");
  Serial.print("AccelY:");
  Serial.print(a.acceleration.y);

  if (a.acceleration.y > 2 || a.acceleration.y <-2 ){
    digitalWrite(LED_Blue, HIGH);
  }
  
  else  {
    digitalWrite(LED_Blue, LOW);
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
}