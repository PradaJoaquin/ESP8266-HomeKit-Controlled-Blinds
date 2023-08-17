# ESP8266-HomeKit-Controlled-Blinds

[README Español](https://github.com/PradaJoaquin/ESP8266-HomeKit-Controlled-Blinds/blob/main/README-es.md)

This project uses a **NodeMCU ESP8266** and **Apple HomeKit** to control an electric blind.

## Motivation
The objective of this project is to control an electric blind through HomeKit, but also keeping the manual use of the blind with its old switch. All this with the lowest possible budget.

The components used were:
- Nodemcu Wifi Esp8266 Board.
- 2 Channel Relay Module (Songle).
- AC 220v to 5v Power Supply.
- Famale-Famale cables and 1mm cables for the electric connections.

The next diagram shows the electric connections:

![Arduino diagram](https://github.com/PradaJoaquin/ESP8266-HomeKit-Controlled-Blinds/assets/36085103/5abb5107-fe2c-4866-ab92-2dfb93dbc56e)

The logic pins used on the **NodeMCU ESP8266** were:
- **D1** (GPIO5) working as *OUTPUT* and used to activate/desactivate the relay so that the blind goes down.
- **D2** (GPIO4) working as *OUTPUT* and used to activate/desactivate the relay so that the blind goes up.
- **D6** (GPIO12) working as *INPUT_PULLUP* and used to know when the physical switch is pulled down.
- **D7** (GPIO13) working as *INPUT_PULLUP* and used to know when the physical switch is pulled up.

## Instalation
1. Download and install the [ch340 driver](https://sparks.gogo.co.nz/ch340.html) required for the computer to recognize the board in Windows 10/11.
2. Download and install the [Arduino IDE](https://www.arduino.cc/en/software).
3. Add the *ESP8266* to the IDE **Boards Manager**, in *Preferences/Additional-Boards-Manager-URLs*. Pasting this link there: *http://arduino.esp8266.com/stable/package_esp8266com_index.json*.
4. Download the *ESP8266* from the IDE **Boards Manager**, in *Tools/Board/Boards-Manager* searching for *ESP8266* and instaling the last version.
5. Download the Library [Arduino-HomeKit-ESP8266](https://github.com/PradaJoaquin/Arduino-HomeKit-ESP8266), and install it from the IDE in *Sketch/IncludeLibrary* selecting the .zip of the downloaded repository. For an explanation of why the fork is used go to the section: [Clarification](#clarification).

## Code Editing
1. Inside the file [wifi_info.h](https://github.com/PradaJoaquin/ESP8266-HomeKit-Controlled-Blinds/blob/main/automatic_blinds/wifi_info.h) change the variable **ssid** for the name of your WiFi and the variable **password** for your WiFi password.
2. Modify the `Serial.begin(9600)` inside the file [automatic_blinds.ino](https://github.com/PradaJoaquin/ESP8266-HomeKit-Controlled-Blinds/blob/main/automatic_blinds/automatic_blinds.ino) with the **BPS** that your device uses, in the case of the NodeMCU ESP8266 this is written on the back of the board.
3. It may be necessary to invert the signals sent to the relays for their correct operation, in my case the relay is activated by sending a LOW signal, with other relays it can be the other way around. If necessary, the functions that interact with the motor should be modified, such as `blind_motor_off()` inside [automatic_blinds.ino](https://github.com/PradaJoaquin/ESP8266-HomeKit-Controlled-Blinds/blob/main/automatic_blinds/automatic_blinds.ino).

## Important settings to modify in the Arduino IDE
- CPU Frequency: 160MHz (Must)
- Board/Module: Generic ESP8266 Module
- Erase Flash: Only Sketch (ideally select *All Flash Contents* when uploading the code for the first time)
- SSL Support: Basic SSL ciphers (lower ROM use)

## Clarification
A [fork](https://github.com/PradaJoaquin/Arduino-HomeKit-ESP8266) of the original library [Arduino-HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266) is used, since with the changes proposed in [#212](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266/pull/212) and coupled with this other change [#2](https://github.com/paullj1/Arduino-HomeKit-ESP8266/pull/2), it is working as intended.

If in the future they update the original repository, which for now seems deprecated, this no longer matters. As of today 7/26/2023 without these changes it does not work.

## Useful Bibliography
- [To know which pins can be used in the NodeMCU ESP8266](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/).
- [For more information on how *INPUT_PULLUP* works](https://aprendiendoarduino.wordpress.com/tag/input-pullup/) (Spanish source). 

## Thanks
- [Arduino-HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266)
- [Arduino-ide](https://github.com/arduino/arduino-ide)
