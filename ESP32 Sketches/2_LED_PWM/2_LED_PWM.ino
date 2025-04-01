#define LED_BUILTIN 2
#define LED_External 13 //Add Variable LED_External and assign it to GPIO13

int DutyCycle = 0; //LED brightness variable, brightnes equals duty cycle
int FadeAmount = 1; // steps of fade
int Delay = 15; //variable called Delay

// the setup function runs once when you press reset or power the board
void setup() {
  
  ledcAttach(LED_External, 8000, 8); // light the external LED using a 8Khz 8-bit PWM
}

// the loop function runs over and over again forever
void loop() {
  
  ledcWrite(LED_External, DutyCycle);
  
  DutyCycle = DutyCycle+FadeAmount;

  // reverse the direction of the fading when the DutyCycle gets to 90%:
 if (DutyCycle >= 90) {
   while(DutyCycle>=0) {
   ledcWrite(LED_External, DutyCycle);
   delay(Delay); // wait for 7 milliseconds to see the dimming effect
   DutyCycle = DutyCycle-FadeAmount;} //decrement DutyCycle
  }
  // wait for 7 milliseconds to see the dimming effect
  delay(Delay);

}
