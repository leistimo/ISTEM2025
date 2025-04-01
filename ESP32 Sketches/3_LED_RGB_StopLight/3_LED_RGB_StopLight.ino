#define LED_BUILTIN 2
#define LED_Green 13 //Add Variable LED_External and assign it to GPIO13
#define LED_Red 14
#define LED_Blue 12

//int DutyCycle = 0; //LED brightness variable, brightnes equals duty cycle
//int FadeAmount = 1; // steps of fade
int Delay = 2000; //variable called Delay

// the setup function runs once when you press reset or power the board
void setup() {
  
  ledcAttach(LED_Red, 8000, 8); // light the external LED using a 8Khz 8-bit PWM
  ledcAttach(LED_Green, 8000, 8);
  ledcAttach(LED_Blue, 8000, 8);

}

// the loop function runs over and over again forever
void loop() {
  
  ledcWrite(LED_Red, 100);
  ledcWrite(LED_Green, 0);
  ledcWrite(LED_Blue, 0);
  
  delay(Delay);

  ledcWrite(LED_Red, 0);
  ledcWrite(LED_Green, 75);
  ledcWrite(LED_Blue, 0);

  delay(Delay);

  ledcWrite(LED_Red, 100);
  ledcWrite(LED_Green, 40);
  ledcWrite(LED_Blue, 0);

  delay(Delay);


}
