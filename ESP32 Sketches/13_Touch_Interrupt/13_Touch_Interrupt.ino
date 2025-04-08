const byte LED_Red = 14;  
int threshold = 50;

bool touch7detected = false;

void gotTouch(){
  touch7detected = true;
}

void setup() {

  Serial.begin(115200);
  pinMode(LED_Red, OUTPUT);
  Serial.println("ESP32 Touch with interrupt");
  delay(1000);
  touchAttachInterrupt(T7, gotTouch, threshold); 
}

void loop() {

  if (touch7detected)
  {
    digitalWrite(LED_Red, HIGH);
    Serial.println("Touch detected (T7)");
    Serial.println(touchRead(T7)); //touchRead() returns the touch value. set touch threshold high to fugure out the touch threshold you want. enjoy :)
    touch7detected =false;
    delay(500);
    digitalWrite(LED_Red, LOW);
  }

}