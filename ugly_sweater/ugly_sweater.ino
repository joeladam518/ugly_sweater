/**
 *  A script for an LED Ugly Sweater using the Arduino LilyPad 
 *  and a RN42 Bluetooth module.
**/

#include <Adafruit_NeoPixel.h>

// Pins:
// Neopixel Pin
//static const int NEO_PIN = 11; 

// Global Variables:
String command;

//static const int NUM_PIXELS = 1;

// Functions:
void ledColor(HardwareSerial &rserial, String color, float percentage)
{   
    rserial.println("");
    rserial.println("");
    rserial.println("**Made in to ledColor**");
    rserial.print("Color = ");
    rserial.println(color);
    rserial.print("percentage = ");
    rserial.println(percentage);
}

void xmasloop(HardwareSerial &rserial, float percentage)
{   
    rserial.println("");
    rserial.println("");
    rserial.println("**Made in to xmasloop**");
    rserial.print("percentage = ");
    rserial.println(percentage);
}

void parseCommand(HardwareSerial &rserial, String com)
{
    // Command examples:
    // ledcolor|color@percentage
    // xmasloop|percentage

    String part1;
    String part2;
    float percentage;

    part1 = com.substring(0, com.indexOf("|"));
    part2 = com.substring(com.indexOf("|") + 1);

    rserial.print("Part 1 = "); rserial.println(part1);
    rserial.print("Part 2 = "); rserial.println(part2);

    if (part1.equals("ledcolor")) {
        
        String inputColor;

        inputColor = part2.substring(0, part2.indexOf("@"));
        percentage = part2.substring(part2.indexOf("@") + 1).toFloat();
        percentage = percentage / 100;

        ledColor(rserial, inputColor, percentage);

    } else if (part1.equals("xmasloop")) {

        percentage = part2.toFloat();
        percentage = percentage / 100;

        xmasloop(rserial, percentage);

    } else {

        rserial.println("Command Not Recognized...");

    }
}

/**************************************************************************************************/

void setup() 
{
    Serial.begin(57600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.println("Serial Connected!");

    // This initializes the NeoPixel library.
    // pixels.begin();
}

void loop() 
{
    if (Serial.available() > 0) {
        char ch = Serial.read();
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
