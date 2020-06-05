#include <time.h>
#include <WiFi.h>
#include <WiFiClient.h>

const unsigned long DELAY = 5; // Must delay in between writing to HEX Display to not cause overlap

// Shift Register Control Pins
//    https://lastminuteengineers.com/74hc595-shift-register-arduino-tutorial/
const int serPin   = 14; // Serial Input Data
const int srclkPin = 27; // Shift Register Clock
const int latchPin = 26; // Register Latch

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

// WiFi Login
const char *ssid     = "ALLOE6CC5";
const char *password = "magicalbird445";

// Realtime variables
unsigned long realtimeMillis = 0; // Keeps track of current milliseconds passed since program start for checking realtime purposes
time_t now = time(nullptr);       // Current real time as time_t
int realTime = 0;                 // Current real time as int i.e 1230

// Alarm variables
const int alarmSetPin = 34; // When this button is pressed, go into Alarm Set Mode
const int alarmDown = 39;   // When this button is pressed, add to the current alarmTime value
const int alarmUp = 36;     // When this button is pressed, subtract from the current alarmTime value
bool alarmTrigger = false;  // Gets set to true if button to configure alarm is pressed
bool alarmGoOff = false;    // Check if the alarm has already gone off
int alarmTime = 0;          // Time for alarm to go off

// Function prototypes
void IRAM_ATTR ISR();

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

  // Update current time since program started
  realtimeMillis = millis();

  // Alarm setup
  pinMode(alarmSetPin, INPUT_PULLUP);     // When button is not pressed, pin will be HIGH. When pressed, button connects pin to GND, setting pin to LOW 
  attachInterrupt(alarmSetPin, ISR, LOW); // Create interrupt for setting Alarm
  pinMode(alarmUp, INPUT_PULLUP);
  pinMode(alarmDown, INPUT_PULLUP);

  delay(3000);
  
}
 
void loop(){

  if(millis() - realtimeMillis > 3000){ // Get current time every 5 seconds as to not hog cpu
    setRealTime(time(nullptr));
    realtimeMillis = millis();
    if(realTime == alarmTime && alarmGoOff == false){
      alarmGoOff = true;
      setOffAlarm();
    }
  }

  if(alarmTrigger == true){ 
    setAlarm();
  }
 
  print_full(realTime);

}

void setOffAlarm(){
  // Zing Zing
}

void setAlarm(){
  detachInterrupt(alarmSetPin); // Turn off interrupts while in this mode
  int currentDigit = 1;
  uint8_t firstDigit = 0;
  uint8_t secondDigit = 0;
  uint8_t thirdDigit = 0;
  uint8_t fourthDigit = 0;
  
  while(true){
    alarmTime = firstDigit*1000 + secondDigit*100 + thirdDigit*10 + fourthDigit;
    print_full(alarmTime);

    if(digitalRead(alarmSetPin) == LOW){
      currentDigit++;
    }

    if(digitalRead(alarmUp) == LOW){
      if(currentDigit == 1){
        zero_nine_check(firstDigit, 1);
      }else if(currentDigit == 2){
        zero_nine_check(secondDigit, 1);
      }else if(currentDigit == 3){
        zero_nine_check(thirdDigit, 1);
      }else if(currentDigit == 4){
        zero_nine_check(fourthDigit, 1);
      }
    }

    if(digitalRead(alarmDown) == LOW){
      if(currentDigit == 1){
        zero_nine_check(firstDigit, 0);
      }else if(currentDigit == 2){
        zero_nine_check(secondDigit, 0);
      }else if(currentDigit == 3){
        zero_nine_check(thirdDigit, 0);
      }else if(currentDigit == 4){
        zero_nine_check(fourthDigit, 0);
      }
    }

    if(currentDigit > 4){
      break;
    }

  }

  attachInterrupt(alarmSetPin, ISR, LOW); // Turn interrupts back on
}

uint8_t zero_nine_check(uint8_t number, bool direction){
  /*
   * Keeps the number between 0-9
   * Direction 0 = Down, Direction 1 = Up
   */
  if(direction == 0){
    if(number == 0){
      number = 9;
    }else{
      number -= 1;
    }
  }else if(direction == 1){
    if(number == 9){
      number = 0;
    }else{
      number += 1;
    }
  }
  
  return number;
}

void IRAM_ATTR ISR() {
  /*
   * Interrupt for setting the alarmTrigger to true when the button is pressed
   */
    alarmTrigger = true;
}

void setRealTime(time_t time){
  // Must subtract 48 due to ascii conversion from char to int i.e. (int)'0' = 48
  realTime = convert_hour((int)ctime(&now)[11] - 48, (int)ctime(&now)[12] - 48, 0);
  realTime = realTime * 10 + convert_hour((int)ctime(&now)[11] - 48, (int)ctime(&now)[12] - 48, 1);
  realTime = realTime * 10 + (int)ctime(&now)[14] - 48;
  realTime = realTime * 10 + (int)ctime(&now)[15] - 48;
}

// The division isolates the needed individual digit
int first_digit(int number){
  return number/1000;
}

int second_digit(int number){
  return (number/100) - (number/1000) * 10;
}

int third_digit(int number){
  return (number/10) - (number/100) * 10;
}

int fourth_digit(int number){
  return (number) - (number/10) * 10;
}

int convert_hour(int first, int second, bool digit){
  /*
   * Converts the first and second digits of the hour into normal time non-military time
   */

  if(first == 0 && second == 0){ // Hour: Midnight = 00
    first = 1;
    second = 2;
  }else if(first == 1 && second > 2){ // Hour: 13 <= x <= 19
    first -= 1;
    second -= 2;
  }else if(first == 2){ // Hour: 20 <= x <= 23
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

void print_full(int number){
  /*
   * Prints the full number to the HEX display
   */
  print_number(first_digit(number),  1);
  print_number(second_digit(number), 2);
  print_number(third_digit(number),  3);
  print_number(fourth_digit(number), 4);
}

void print_number(int number, int digit){
  /*
   * Decide which byte to write to the display based on the input number
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
  /*
   * Writes the HEX-byte representation of the number to the Shift Register to be displayed on the HEX Display
   */

  number = number | check_decimal(digit); // Make the decimal point bit one if digit = 2 

  select_digit(digit); // Turn off all other digits besides the one being written to
  all_low(); // Must reset all segments for the current digit or else the previous digit's segments will appear
  digitalWrite(latchPin, 0); // Lower the latch signal in order to output bits on the shift register
  shiftOut(serPin, srclkPin, LSBFIRST, number);  // Makes the bits appear in order on the Shift Register Output i.e A = MSB, H = LSB
  digitalWrite(latchPin, 1);
  delay(DELAY);  // Need delay here or numbers on display will be illegible
}

void select_digit(int digit){
  /*
   * Deselect all digits then select the one needed to be written to
   * 0 is on, 1 is off
   */

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