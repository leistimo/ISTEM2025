#define LED_Red 14
#define LED_Green 13
#define LED_Blue 12

const byte Photo_Resistor = 39;

void setup() {

  ledcAttach(LED_Red, 8000, 8);
  ledcAttach(LED_Green, 8000, 8);
  ledcAttach(LED_Blue, 8000, 8);

  ledcWrite(LED_Red, 0);
  ledcWrite(LED_Green, 0);
  ledcWrite(LED_Blue, 0);

  Serial.begin(115200);
  //analogSetWidth(9); // Default resolution is 12 bits. (Choose 9-12)
}

void loop() {
  Serial.println(analogRead(Photo_Resistor));

  if (analogRead(Photo_Resistor)>500)
  {
    ledcWrite(LED_Red, 100);
    ledcWrite(LED_Green, 100);
    ledcWrite(LED_Blue, 100);
  }
  else
  {
    ledcWrite(LED_Red, 0);
    ledcWrite(LED_Green, 0);
    ledcWrite(LED_Blue, 0);
  }
  delay(500);
  }
