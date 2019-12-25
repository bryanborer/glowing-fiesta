// the number of the LED pin
const int ledPin = 16;  // 16 corresponds to GPIO16
const int otherPin = 4;

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
 
void setup(){
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);
  ledcWrite(ledChannel, 128);

  pinMode(otherPin, OUTPUT);
}
 
void loop(){
  digitalWrite(otherPin, 0);
  delayMicroseconds(100);
  digitalWrite(otherPin, 1);
  delayMicroseconds(100);
  }