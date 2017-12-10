/**
 *  A script for an LED Ugly Sweater using the Arduino LilyPad 
 *  and a RN42 Bluetooth module.
**/

#include <Adafruit_NeoPixel.h>

// Pins:

// NeoPixel Pin #
static const int NEO_PIN = 11; 

// Global Variables:

String command;

// Functions:

// Set the color by given name.
// Should I just set the values directly? 
// example: int color[3] = color[0](red), color[1](green), color[2](blue)
void setColor(HardwareSerial &rserial, String color, float percentage)
{   
    rserial.println("");
    rserial.println("");
    rserial.println("**Made in to setColor**");
    rserial.print("Color = ");
    rserial.println(color);
    rserial.print("percentage = ");
    rserial.println(percentage);
}

// Loop between red and green. 
// "wait" slows the Loop down.
void xmasloop(HardwareSerial &rserial, int wait)
{   
    rserial.println("");
    rserial.println("");
    rserial.println("**Made in to xmasloop**");
    rserial.print("wait = ");
    rserial.println(wait);
}

// Parses the incoming command for what to do...
void parseCommand(HardwareSerial &rserial, String com)
{
    String part1;
    String part2;

    // Command examples:
    // setcolor|color@percentage
    // xmasloop|delay

    part1 = com.substring(0, com.indexOf("|"));
    part2 = com.substring(com.indexOf("|") + 1);

    rserial.print("Part 1 = "); rserial.println(part1);
    rserial.print("Part 2 = "); rserial.println(part2);

    if (part1.equals("setcolor")) {
        String inputColor = part2.substring(0, part2.indexOf("@"));
        float percentage = part2.substring(part2.indexOf("@") + 1).toFloat();
        percentage = percentage / 100;

        setColor(rserial, inputColor, percentage);
    } else if (part1.equals("xmasloop")) {
        int wait = part2.toInt();

        xmasloop(rserial, wait);
    } else {
        rserial.println("Command Not Recognized...");
    }
}

/**************************************************************************************************/

void setup() {
    // Both the bluetooth module and the Arduino have to be set to the same baud rate.
    // The default baud for the RN42 bluetooth module is 115200.
    // Was having trouble, So I set both to 57600 and things started working.
    // RN42 Wiki: https://eewiki.net/display/Wireless/Getting+Started+with+RN42+Bluetooth+Module
    Serial.begin(57600);
    Serial.println("Serial Connected!");
}

void loop() {
    if (Serial.available() > 0) {
        char ch = Serial.read();

        // Print What comes in...
        Serial.print("-"); Serial.print(ch); Serial.print("-");
        
        if (ch == '\n') {
            Serial.println("");
            Serial.println("");

            parseCommand(Serial, command);
            command = "";
        } else {
            command += ch;
        }
    }
}
