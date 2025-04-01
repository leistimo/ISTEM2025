
const byte Vpot = 36;

void setup() {

  Serial.begin(9600); //initialize Serial Communication at 9600 bits per second

}

void loop() {
  
  Serial.println(analogRead(Vpot)); //Writes value to the serial monitor

}
