/**
 *  A script for an LED Ugly Sweater using the Arduino LilyPad 
 *  and a RN42 Bluetooth module.
**/

#include <Adafruit_NeoPixel.h>
#include <advancedSerial.h>

// Pins:
// Neopixel Pin
//static const int NEO_PIN = 11; 

// Global Variables:
String command;

// Number of neopixels
//static const int NUM_PIXELS = 1;

// Initialize the neopixel object:
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);

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
void ledColor(HardwareSerial &rserial, String color, int percentage)
{   
    rserial.println("");
    rserial.println("**Made in to ledColor**");
    rserial.print("Color = ");
    rserial.print(color);
    rserial.print("percentage = ");
    rserial.print(percentage);

    // Display Color (dc):
    //int (*dc)[3];

    // if (color.equals("on")) {
    //     dc = &on;
    // } else if (color.equals("off")) {
    //     dc = &off;
    // } else if (color.equals("red")) {
    //     dc = &red;
    // } else if (color.equals("green")) {
    //     dc = &green;
    // } else if (color.equals("blue")) {
    //     dc = &blue;
    // } else if (color.equals("cyan")) {
    //     dc = &cyan;
    // } else if (color.equals("magenta")) {
    //     dc = &magenta;
    // } else if (color.equals("yellow")) {
    //     dc = &yellow;
    // } else {
    //     rserial.println("Color Not recognized...");
    // }

    // rserial.println((uint8_t) dc[0]);
    // rserial.println((uint8_t) dc[1]);
    // rserial.println((uint8_t) dc[2]);
    
    // for (int i = 0; i < NUM_PIXELS; i++) {
    //     // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    //     pixels.setPixelColor(i, pixels.Color((uint8_t) dc[0], (uint8_t) dc[1], (uint8_t) dc[2]));
    //     // This sends the updated pixel color to the hardware.
    //     pixels.show();
    // }
}

// void ledLoop(HardwareSerial &rserial, float maxpercentage)
// {

// }

// void xmasLoop(HardwareSerial &rserial, float maxpercentage)
// {

// }

// void parseCommand(HardwareSerial &rserial, String com)
// {
//     String part1;
//     String part2;
//     float percentage;

//     // Command examples:
//     // command|whattodowithcommand@percentage
//     // xmasloop|maxpercentage
//     // ledcolor|color@percentage
//     //  ledloop|color1,color2,color(etc)...@maxpercentage

//     part1 = com.substring(0, com.indexOf("|"));
//     part2 = com.substring(com.indexOf("|") + 1);

//     if (part1.equals("xmasloop")) {

//         percentage = part2.toFloat();
//         percentage = percentage / 100;
        
//         xmasLoop(percentage);

//     } else if (part1.equals("ledcolor")) {
//         String inputColor;
//         String percentage_str;

//         inputColor = part2.substring(0, part2.indexOf("@"));
//         percentage_str = part2.substring(part2.indexOf("@") + 1);
//         percentage = percentage_str.toFloat();
//         percentage = percentage / 100;

//         rserial.println("hello!");

//         ledColor(rserial, inputColor, percentage);

//     } else if (part1.equals("ledloop")) {

//     } else {
//         rserial.println("Command Not Recognized...");
//     }
// }

/**************************************************************************************************/

void setup() 
{
    Serial.begin(57600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.println("Serial Connected!");
    digitalWrite(13,HIGH);

    // This initializes the NeoPixel library.
    // pixels.begin();
}

void loop() 
{
    if (Serial.available() > 0) {
        Serial.println("Serial Available!");
        Serial.println("-----");
        
        char ch = Serial.read();

        Serial.println(chr);
        Serial.println("-----");

        if (ch == '\n') {
            //parseCommand(rs, command);
            //command = "";
        } else {
            command += ch;
        }
    }
}
