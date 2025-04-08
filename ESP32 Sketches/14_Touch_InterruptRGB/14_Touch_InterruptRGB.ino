const byte LED_Red = 14;  
const byte LED_Blue = 12;
const byte LED_Green = 13;
int threshold = 50;

bool touch7detected = false;
bool touch8detected = false;
bool touch9detected = false;

void gotTouch7(){
 
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Blue, LOW);
  digitalWrite(LED_Red, HIGH);
  touch7detected = true;
  touch8detected = false;
  touch9detected = false;
}

void gotTouch8(){
 
  digitalWrite(LED_Blue, LOW);
  digitalWrite(LED_Red, LOW);
  digitalWrite(LED_Green, HIGH);
  touch8detected = true;
  touch7detected = false;
  touch9detected = false;
}

void gotTouch9(){
  
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Red, LOW);
  digitalWrite(LED_Blue, HIGH);
  touch9detected = true;
  touch7detected = false;
  touch8detected = false;
  
}

void setup() {

  Serial.begin(115200);
  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Blue, OUTPUT);
  pinMode(LED_Green, OUTPUT);
  Serial.println("ESP32 Touch with interrupt");
  delay(1000);
  touchAttachInterrupt(T7, gotTouch7, threshold);
  touchAttachInterrupt(T8, gotTouch8, threshold); 
  touchAttachInterrupt(T9, gotTouch9, threshold);

  digitalWrite(LED_Red, LOW);
  digitalWrite(LED_Blue, LOW);
}

void loop() {

  if (touch7detected)
  {
    digitalWrite(LED_Green, LOW);
    digitalWrite(LED_Blue, LOW);
    digitalWrite(LED_Red, HIGH);
    
    Serial.print(T7);
    Serial.println(" Touch detected (T7)");
    touch7detected =false;
    touch8detected =false;
    touch9detected =false;
    delay(500);
    digitalWrite(LED_Red, LOW);
  }

  if (touch8detected)
  {
    digitalWrite(LED_Red, LOW);
    digitalWrite(LED_Blue, LOW);
    digitalWrite(LED_Green, HIGH);
    Serial.print(T8);
    Serial.println(" Touch detected (T8)");
    touch8detected =false;
    touch7detected =false;
    touch9detected =false;
    delay(500);
    digitalWrite(LED_Green, LOW);
  }

  if (touch9detected)
  {
    digitalWrite(LED_Red, LOW);
    digitalWrite(LED_Green, LOW);
    digitalWrite(LED_Blue, HIGH);
    Serial.print(T9);
    Serial.println(" Touch detected (T9)");
    touch9detected =false;
    touch7detected =false;
    touch8detected =false;
    delay(500);
    digitalWrite(LED_Blue, LOW);
  }

  

}