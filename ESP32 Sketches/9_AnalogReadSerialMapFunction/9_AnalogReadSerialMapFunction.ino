#define LED_Green 13
#define LED_Red 14
#define LED_Blue 12
const byte Vpot = 36;
int DutyCycle;

void setup() {

  Serial.begin(9600); //initialize Serial Communication at 9600 bits per second
  pinMode(LED_Green, OUTPUT);
  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Blue, OUTPUT);
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Red, LOW);
  digitalWrite(LED_Blue, LOW);
}
void loop() {

  DutyCycle=analogRead(Vpot);
  DutyCycle=map(DutyCycle,0, 4095, 0, 100); //Map function changes the analogRead range from 0 - 4095 to 0 - 100

  Serial.print(DutyCycle); 
  Serial.println("%DC");
  delay(500);
  
}





 /*
  if (analogRead(Vpot)< 1365){
    Serial.print(analogRead(Vpot)); //Writes value to the serial monitor
    Serial.println(" Red LED ON");
    digitalWrite(LED_Green, LOW);
    digitalWrite(LED_Red, HIGH);
    digitalWrite(LED_Blue, LOW);
    delay(1000);
  }
    else if (1365<analogRead(Vpot) && analogRead(Vpot)< 2730){
    Serial.print(analogRead(Vpot));
    Serial.println(" Green LED ON");
    digitalWrite(LED_Green, HIGH);
    digitalWrite(LED_Red, LOW);
    digitalWrite(LED_Blue, LOW);
    delay(1000);
  }
    else if (analogRead(Vpot)> 2730){
    Serial.print(analogRead(Vpot));
    Serial.println(" Blue LED ON");
    digitalWrite(LED_Green, LOW);
    digitalWrite(LED_Red, LOW);
    digitalWrite(LED_Blue, HIGH);
    delay(1000);
  }
    else {
    Serial.println(analogRead(Vpot));
    Serial.println("Error");
    digitalWrite(LED_Green, LOW);
    digitalWrite(LED_Red, LOW);
    digitalWrite(LED_Blue, LOW);
    delay(1000);
  }
  */
