/**
 *  A script for an LED Ugly Sweater using the Arduino LilyPad 
 *  and a RN42 Bluetooth module.
**/

#include <Adafruit_NeoPixel.h>
#include <advancedSerial.h>

// Global Variables:
String command;

// Functions:
void parseCommand(String com)
{
    String part1;
    String part2;

    part1 = com.substring(0, com.indexOf(" "));
    part2 = com.substring(com.indexOf(" ") + 1);

    switch (part1) {
        case "pinon":

            break;
        case "pinoff":

            break;
        default:

            break;
    }
}

/**************************************************************************************************/

void setup() {
    Serial.begin(115200);
}

void loop() {
    if (Serial.available()) {
        char c = Serial.read();

        if (c == '\n') {
            parseCommand(command);
            command = "";
        } else {
            command += c;
        }
    }
}
