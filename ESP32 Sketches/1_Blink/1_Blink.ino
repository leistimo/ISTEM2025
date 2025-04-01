#define LED_BUILTIN 2
#define LED_External 13 //Add Variable LED_External and assign it to GPIO13

// the setup function runs once when you press reset or power the board
void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);   // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_External, OUTPUT);  // initialize digital pin LED_External as an output.

  digitalWrite(LED_BUILTIN, LOW);   // initialize low or off. 
  digitalWrite(LED_External, LOW);  // initialize low or off.

}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_External, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_External, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}
