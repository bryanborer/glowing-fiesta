#include <time.h>
#include <WiFi.h>
#include <WiFiClient.h>

const unsigned long DELAY = 5; // Must delay in between writing to HEX Display to not cause overlap

// Shift Register Control Pins
//    https://lastminuteengineers.com/74hc595-shift-register-arduino-tutorial/
const int serPin   = 14; // Serial Input Data
const int srclkPin = 27; // Shift Register Clock
const int latchPin = 26; // Register Latch

byte data; // Data to be sent through the shift register to the HEx Display to control the segments

// These pin assignments are according to these diagrams:
//    https://github.com/thehookup/ESP32_Ceiling_Light/blob/master/GPIO_Limitations_ESP32_NodeMCU.jpg
//    http://thomas.bibby.ie/using-the-kyx-5461as-4-digit-7-segment-led-display-with-arduino/
// HEX Display pins are connected to the shift register such that Output QA of Shift Register -> Segment A of HEX (Pin 11)
const int dig1 = 19; // Digit 1
const int dig2 = 18; // Digit 2
const int dig3 = 5;  // Digit 3
const int dig4 = 17; // Digit 4

// Byte definitions for HEX display numbers
const uint8_t allLow  = 0x00; // 0000 0000
const uint8_t allHigh = 0xFF; // 1111 1111
const uint8_t zero    = 0xFC; // 1111 1110
const uint8_t one     = 0x60; // 0110 0000
const uint8_t two     = 0xDA; // 1101 1010
const uint8_t three   = 0xF2; // 1111 0010
const uint8_t four    = 0x66; // 0110 0110
const uint8_t five    = 0xB6; // 1011 0110
const uint8_t six     = 0xBE; // 1011 1110
const uint8_t seven   = 0xE0; // 1110 0000
const uint8_t eight   = 0xFE; // 1111 1110
const uint8_t nine    = 0xF6; // 1111 0110

const char *ssid     = "ALLOE6CC5";
const char *password = "magicalbird445";

unsigned long currentMillis = 0; // Keeps track of current milliseconds passed since program start 
time_t now = time(nullptr);      // Current real time
 
void setup(){
  // Start serial port for ESP32
  Serial.begin(115200);

  // Shift Register Setup
  pinMode(serPin, OUTPUT);
  pinMode(srclkPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  // Setup pins for HEX
  pinMode(dig1, OUTPUT);
  pinMode(dig2, OUTPUT);
  pinMode(dig3, OUTPUT);
  pinMode(dig4, OUTPUT);

  digitalWrite(dig1, 0);

  pinMode(25, OUTPUT);

  digitalWrite(25, 1);

  
  // Setup wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  Serial.print("\nWaiting for WiFi Connection");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.print("\nConnected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Get time from internet
  //    void configTime(int timezone, int daylightOffset_sec, const char* server1, const char* server2, const char* server3)
  //    (-6) represents Central Standard Time
  configTime((-6) * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");

  delay(1000);          // Wait for time to be retrieved from internet
  now = time(nullptr);  // Update real time variable
  Serial.println(ctime(&now));
  // Serial.println(ctime(&now)[11]);
  // Serial.println((char)ctime(&now)[11]);
  // Serial.println((int)ctime(&now)[11]);

  currentMillis = millis();
  
}
 
void loop(){

  if(millis() - currentMillis > 5000){ // Get current time every 5 seconds as to not hog cpu
    now = time(nullptr);
    currentMillis = millis();
  }

  // Must subtract 48 due to ascii conversion from char to int i.e. (int)'0' = 48
  print_number(convert_hour((int)ctime(&now)[11] - 48, (int)ctime(&now)[12] - 48, 0), 1);
  print_number(convert_hour((int)ctime(&now)[11] - 48, (int)ctime(&now)[12] - 48, 1), 2);
  print_number((int)ctime(&now)[14] - 48, 3);
  print_number((int)ctime(&now)[15] - 48, 4);

}


int convert_hour(int first, int second, bool digit){
  /*
   * Converts the first and second digits of the hour into normal time non-military time
   */

  if(first == 1 && second > 2){ // Hour: 12 <= x <= 19
    first -= 1;
    second -= 2;
  } else if(first == 2){ // Hour: 20 <= x <= 23
    int number = (first * 10) + second;
    number -= 12;
    first = number / 10;
    second = number - (first * 10);
  }
  if(digit == 0){
    return first;
  }else{
    return second;
  }
  
}

void print_number(int number, int digit){
  /*
   * Prints the desired number 0-9 on the desired digit 1-4
   */

  if(number == 0){
    write_hex(zero, digit);
  }else if(number == 1){
    write_hex(one, digit);
  }else if(number == 2){
    write_hex(two, digit);
  }else if(number == 3){
    write_hex(three, digit);
  }else if(number == 4){
    write_hex(four, digit);
  }else if(number == 5){
    write_hex(five, digit);
  }else if(number == 6){
    write_hex(six, digit);
  }else if(number == 7){
    write_hex(seven, digit);
  }else if(number == 8){
    write_hex(eight, digit);
  }else if(number == 9){
    write_hex(nine, digit);
  }
}

void write_hex(uint8_t number, int digit){
  number = number | check_decimal(digit); // Make the decimal point bit one if digit = 2 

  select_digit(digit);
  all_low();
  digitalWrite(latchPin, 0);
  shiftOut(serPin, srclkPin, LSBFIRST, number);  // Makes the bits appear in order on the Shift Register Output i.e A = MSB, H = LSB
  digitalWrite(latchPin, 1);
  delay(DELAY);
}

void select_digit(int digit){
  digitalWrite(dig1, 1);
  digitalWrite(dig2, 1);
  digitalWrite(dig3, 1);
  digitalWrite(dig4, 1);

  if(digit == 1){
    digitalWrite(dig1, 0);
  }else if(digit == 2){
    digitalWrite(dig2, 0);
  }else if(digit == 3){
    digitalWrite(dig3, 0);
  }else if(digit == 4){
    digitalWrite(dig4, 0);
  }
}

void all_low(){
  /*
   * Turns off all segments of the current digit
   */
  digitalWrite(latchPin, 0);
  shiftOut(serPin, srclkPin, LSBFIRST, allLow);  // Makes the bits appear in order on the Shift Register Output i.e A = MSB, H = LSB
  digitalWrite(latchPin, 1);
}

uint8_t check_decimal(int digit){
  /*
   * Only need to turn on the decimal point between the 2nd and 3rd digits
   */
  if(digit == 2){
    return 1;
  }else{
    return 0;
  }
}