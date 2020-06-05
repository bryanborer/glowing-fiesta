# glowing-fiesta

Alarm Clock project using an ESP32 (see below for the specific ESP32 board)
 * Written in C with Arduino Framework
    * Using VSCode with Arduino extension to develop
 * ESP32 is connected to 4-digit HEX Display to show current time
    * Connects to the internet to retrieve current real time
    * Outputs to Shift register which then outputs to the HEX Display

### Instructions
 * Install Arduino from https://www.arduino.cc/ (Microsoft Store download does not path correctly)
 * Install Arduino Extension for VSCode 
 * Follow this tutorial -> https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
    * Either do all the steps in VSCode itself or do it in Arduino IDE and then restart VSCode
 * Select ESP32 Dev Module (esp32) in Board Config (ctrl + shift + p)
 * Select correct Serial Port
 * Upload
    * May need to hold IOO button down when Serial Port says "Connecting..."

### Useful Resources
http://www.thesmarthomehookup.com/post-320/
https://github.com/thehookup/ESP32_Ceiling_Light/blob/master/GPIO_Limitations_ESP32_NodeMCU.jpg
https://www.instructables.com/id/ESP32-Internal-Details-and-Pinout/

### NOTE
Main development is proceeding in the **shift_register_hex** folder. Micropython and hex.ino were used only to further my understanding of the software and hardware.

