/**
 *  A script for an LED Ugly Sweater using the Arduino LilyPad 
 *  and a RN42 Bluetooth module.
**/

#include <Adafruit_NeoPixel.h>

// Pins:

static const int NEO_PIN = 6;

// Global Variables:

// To hold commands coming in through serial
String command;
// Number of neopixels
static const int NUM_NEOPIXELS = 1;
// Initialize the NeoPixel Object 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_NEOPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ400);

// Color arrays
int off[3] = { 0, 0, 0 };
int on[3]  = { 255, 255, 255 };
int red[3] = { 255, 0, 0 };
int green[3] = { 0, 255, 0 };
int blue[3] = { 0, 0, 255 };
int cyan[3] = { 0, 255, 255 };
int magenta[3] = { 255, 0, 255 };
int yellow[3] = { 255, 255, 0 };

// Functions:

// Set the color by given name.
// Should I just set the values directly? 
// example: int color[3] = color[0](red), color[1](green), color[2](blue)
int setColor(HardwareSerial &rserial, String color, float percentage)
{   
    rserial.println("**Made in to setColor**");
    rserial.print("color = "); rserial.println(color);
    rserial.print("percentage = "); rserial.println(percentage);
    rserial.println("");

    int color_array[3];

    // A little defensive driving
    if (percentage > 1) {
        percentage = 1;
    }
    if (percentage < 0) {
        percentage = 0;
    }

    if (color.equals("on")) {
        color_array[0] = on[0];
        color_array[1] = on[1];
        color_array[2] = on[2];
    } else if (color.equals("off")) {
        color_array[0] = off[0];
        color_array[1] = off[1];
        color_array[2] = off[2];
    } else if (color.equals("red")) {
        color_array[0] = red[0] * percentage;
        color_array[1] = red[1] * percentage;
        color_array[2] = red[2] * percentage;
    } else if (color.equals("green")) {
        color_array[0] = green[0] * percentage;
        color_array[1] = green[1] * percentage;
        color_array[2] = green[2] * percentage;
    } else if (color.equals("blue")) {
        color_array[0] = blue[0] * percentage;
        color_array[1] = blue[1] * percentage;
        color_array[2] = blue[2] * percentage;
    } else if (color.equals("cyan")) {
        color_array[0] = cyan[0] * percentage;
        color_array[1] = cyan[1] * percentage;
        color_array[2] = cyan[2] * percentage;
    } else if (color.equals("magenta")) {
        color_array[0] = magenta[0] * percentage;
        color_array[1] = magenta[1] * percentage;
        color_array[2] = magenta[2] * percentage;
    } else if (color.equals("yellow")) {
        color_array[0] = yellow[0] * percentage;
        color_array[1] = yellow[1] * percentage;
        color_array[2] = yellow[2] * percentage;
    } else {
        rserial.println("Color Not recognized...");
        return 0;
    }

    // Debug
    rserial.print("color_array[0] = "); rserial.println(color_array[0]);
    rserial.print("color_array[1] = "); rserial.println(color_array[1]);
    rserial.print("color_array[2] = "); rserial.println(color_array[2]);
    rserial.println("");

    for (int i = 0; i < NUM_NEOPIXELS; i++) {
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(color_array[0], color_array[1], color_array[2]));
        // This sends the updated pixel color to the hardware.
        pixels.show();
    }

    return 1;
}

// Loop between red and green. 
// "wait" slows the Loop down.
int xmasloop(HardwareSerial &rserial, int wait)
{   
    rserial.println("**Made in to xmasloop**");
    rserial.print("wait = "); rserial.println(wait);
    rserial.println("");

    return 1;
}

// Parses the incoming command for what to do...
int parseCommand(HardwareSerial &rserial, String com)
{
    String part1;
    String part2;

    // Command examples:
    // setcolor|color@percentage
    // xmasloop|delay

    part1 = com.substring(0, com.indexOf("|"));
    part2 = com.substring(com.indexOf("|") + 1);

    // Debug
    rserial.print("Part 1 = "); rserial.println(part1);
    rserial.print("Part 2 = "); rserial.println(part2);
    rserial.println("");

    if (part1.equals("setcolor")) {
        String inputColor;
        float percentage;
        if (part2.indexOf("@") > 0){
            inputColor = part2.substring(0, part2.indexOf("@"));
            percentage = part2.substring(part2.indexOf("@") + 1).toFloat();
            percentage = percentage / 100;
            if (setColor(rserial, inputColor, percentage) == 0) {
                return 0;
            }
        } else {
            inputColor = part2;
            if (setColor(rserial, inputColor, 1) == 0) {
                return 0;
            }
        }
    } else if (part1.equals("xmasloop")) {
        int wait = part2.toInt();
        if (xmasloop(rserial, wait) == 0) {
            return 0;
        }
    } else {
        rserial.println("Command Not Recognized...");
        return 0;
    }

    return 1;
}

/**************************************************************************************************/

void setup() {
    // Both the bluetooth module and the Arduino have to be set to the same baud rate.
    // The default baud for the RN42 bluetooth module is 115200.
    // Was having trouble, So I set both to 57600 and things started working.
    // RN42 Wiki: https://eewiki.net/display/Wireless/Getting+Started+with+RN42+Bluetooth+Module
    Serial.begin(57600);
    Serial.println("Serial Connected!");

    // This initializes the NeoPixels
    pixels.begin();
}

void loop() {
    if (Serial.available()) {
        char ch = Serial.read();

        // Debug
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
