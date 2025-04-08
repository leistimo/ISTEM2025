
const byte LED_GPIO = 14;  // Marked volatile so it can be read inside the ISR

void setup() {

  Serial.begin(115200);
  pinMode(LED_GPIO, OUTPUT);
  Serial.println("ESP32 Touch Test");
  delay(1000);
}

void loop() {

  Serial.println(touchRead(T7)); //get value and print value of T7 (GPIO27)

  if (touchRead(T7)<40)
    digitalWrite(LED_GPIO, HIGH);
  else
    digitalWrite(LED_GPIO, LOW);

  delay(500);

}