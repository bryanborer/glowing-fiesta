#include <time.h>
#include <WiFi.h>
#include <WiFiClient.h>

const unsigned long DELAY = 5; // Must delay in between writing to HEX Display to not cause overlap

// These pin assignments are according to these diagrams:
//    https://github.com/thehookup/ESP32_Ceiling_Light/blob/master/GPIO_Limitations_ESP32_NodeMCU.jpg
//    http://thomas.bibby.ie/using-the-kyx-5461as-4-digit-7-segment-led-display-with-arduino/
const int segA = 16; // A
const int segB = 27; // B
const int segC = 26; // C
const int segD = 25; // D
const int segE = 33; // E
const int segF = 4;  // F
const int segG = 14; // G
const int dp = 32;   // Decimal Point

const int dig1 = 19; // Digit 1
const int dig2 = 18; // Digit 2
const int dig3 = 5;  // Digit 3
const int dig4 = 17; // Digit 4

const char *ssid = "ALLOE6CC5";
const char *password = "magicalbird445";

unsigned long currentMillis = 0; // Keeps track of current milliseconds passed since program start 
time_t now = time(nullptr);      // Current real time

void setup(){
  // Start serial port for ESP32
  Serial.begin(115200);

  // Setup pins for HEX
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(dp, OUTPUT);
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
  } else{
    return second;
  }
  
}

void print_number(int number, int digit){
  /*
   * Prints the desired number 0-9 on the desired digit 1-4
   */

  if(number == 0){
    zero(digit);
  }
  if(number == 1){
    one(digit);
  }
  if(number == 2){
    two(digit);
  }
  if(number == 3){
    three(digit);
  }
  if(number == 4){
    four(digit);
  }
  if(number == 5){
    five(digit);
  }
  if(number == 6){
    six(digit);
  }
  if(number == 7){
    seven(digit);
  }
  if(number == 8){
    eight(digit);
  }
  if(number == 9){
    nine(digit);
  }
}

void all_low(){
  /*
   * Turns off all segments of the current digit
   */
  digitalWrite(segA, 0);
  digitalWrite(segB, 0);
  digitalWrite(segC, 0);
  digitalWrite(segD, 0);
  digitalWrite(segE, 0);
  digitalWrite(segF, 0);
  digitalWrite(segG, 0);
  digitalWrite(dp, 0);
}

void all_high(){
  /*
   * Turns on all segments of the current digit
   */
  digitalWrite(segA, 1);
  digitalWrite(segB, 1);
  digitalWrite(segC, 1);
  digitalWrite(segD, 1);
  digitalWrite(segE, 1);
  digitalWrite(segF, 1);
  digitalWrite(segG, 1);
  digitalWrite(dp, 1);
}

void zero(int digit){
  all_low();
  select_digit(digit);
  digitalWrite(segA, 1);
  digitalWrite(segB, 1);
  digitalWrite(segC, 1);
  digitalWrite(segD, 1);
  digitalWrite(segE, 1);
  digitalWrite(segF, 1);
  digitalWrite(segG, 0);
  check_decimal(digit);
  delay(DELAY);
}

void one(int digit){
  all_low();
  select_digit(digit);
  digitalWrite(segA, 0);
  digitalWrite(segB, 1);
  digitalWrite(segC, 1);
  digitalWrite(segD, 0);
  digitalWrite(segE, 0);
  digitalWrite(segF, 0);
  digitalWrite(segG, 0);
  check_decimal(digit);
  delay(DELAY);
}

void two(int digit){
  all_low();
  select_digit(digit);
  digitalWrite(segA, 1);
  digitalWrite(segB, 1);
  digitalWrite(segC, 0);
  digitalWrite(segD, 1);
  digitalWrite(segE, 1);
  digitalWrite(segF, 0);
  digitalWrite(segG, 1);
  check_decimal(digit);
  delay(DELAY);
}

void three(int digit){
  all_low();
  select_digit(digit);
  digitalWrite(segA, 1);
  digitalWrite(segB, 1);
  digitalWrite(segC, 1);
  digitalWrite(segD, 1);
  digitalWrite(segE, 0);
  digitalWrite(segF, 0);
  digitalWrite(segG, 1);
  check_decimal(digit);
  delay(DELAY);
}

void four(int digit){
  all_low();
  select_digit(digit);
  digitalWrite(segA, 0);
  digitalWrite(segB, 1);
  digitalWrite(segC, 1);
  digitalWrite(segD, 0);
  digitalWrite(segE, 0);
  digitalWrite(segF, 1);
  digitalWrite(segG, 1);
  check_decimal(digit);
  delay(DELAY);
}

void five(int digit){
  all_low();
  select_digit(digit);
  digitalWrite(segA, 1);
  digitalWrite(segB, 0);
  digitalWrite(segC, 1);
  digitalWrite(segD, 1);
  digitalWrite(segE, 0);
  digitalWrite(segF, 1);
  digitalWrite(segG, 1);
  check_decimal(digit);
  delay(DELAY);
}

void six(int digit){
  all_low();
  select_digit(digit);
  digitalWrite(segA, 1);
  digitalWrite(segB, 0);
  digitalWrite(segC, 1);
  digitalWrite(segD, 1);
  digitalWrite(segE, 1);
  digitalWrite(segF, 1);
  digitalWrite(segG, 1);
  check_decimal(digit);
  delay(DELAY);
}

void seven(int digit){
  all_low();
  select_digit(digit);
  digitalWrite(segA, 1);
  digitalWrite(segB, 1);
  digitalWrite(segC, 1);
  digitalWrite(segD, 0);
  digitalWrite(segE, 0);
  digitalWrite(segF, 0);
  digitalWrite(segG, 0);
  check_decimal(digit);
  delay(DELAY);
}

void eight(int digit){
  all_low();
  select_digit(digit);
  digitalWrite(segA, 1);
  digitalWrite(segB, 1);
  digitalWrite(segC, 1);
  digitalWrite(segD, 1);
  digitalWrite(segE, 1);
  digitalWrite(segF, 1);
  digitalWrite(segG, 1);
  check_decimal(digit);
  delay(DELAY);
}

void nine(int digit){
  all_low();
  select_digit(digit);
  digitalWrite(segA, 1);
  digitalWrite(segB, 1);
  digitalWrite(segC, 1);
  digitalWrite(segD, 1);
  digitalWrite(segE, 0);
  digitalWrite(segF, 1);
  digitalWrite(segG, 1);
  check_decimal(digit);
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

void check_decimal(int digit){
  /*
   * Only need to turn on the decimal point between the 2nd and 3rd digits
   */
  if(digit == 2){
    digitalWrite(dp, 1);
  }else{
    digitalWrite(dp, 0);
  }
}