const byte Photo_Resistor = 39;

void setup() {
  Serial.begin(115200);
  //analogSetWidth(9); // Default resolution is 12 bits. (Choose 9-12)
}

void loop() {
  Serial.println(analogRead(Photo_Resistor));
  delay(500);
  }
