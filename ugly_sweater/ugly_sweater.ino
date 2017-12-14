/**
 *  A script for an LED Ugly Sweater using the Arduino LilyPad 
 *  and a RN42 Bluetooth module.
**/

#include <Adafruit_NeoPixel.h>

// Pins:

static const int NEO_PIN = 5;

// Global Variables:

// Number of neopixels
static const int NUM_NEOPIXELS = 3;

// Initialize the NeoPixel Object // NEO_KHZ400
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_NEOPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);

// To hold commands coming in through serial
String command;

// LED Color Pin Enum
static const int R = 0;
static const int G = 1;
static const int B = 2;

// Color arrays
int off[3] = { 0, 0, 0 };
int on[3]  = { 255, 255, 255 };
int red[3] = { 255, 0, 0 };
int green[3] = { 0, 255, 0 };
int blue[3] = { 0, 0, 255 };
int cyan[3] = { 0, 255, 255 };
int magenta[3] = { 255, 0, 255 };
int yellow[3] = { 255, 255, 0 };

int currentcolor[3] = { 0, 0, 0 };

// Functions:

void setEveryPixelsColor(int color[3]) 
{
    for (int i = 0; i < NUM_NEOPIXELS; i++) {
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(color[R], color[G], color[B]));
        pixels.show(); // This sends the updated pixel color to the hardware.
    }

    currentcolor[R] = color[R];
    currentcolor[G] = color[G];
    currentcolor[B] = color[B];
}

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
        color_array[R] = on[R];
        color_array[G] = on[G];
        color_array[B] = on[B];
    } else if (color.equals("off")) {
        color_array[R] = off[R];
        color_array[G] = off[G];
        color_array[B] = off[B];
    } else if (color.equals("red")) {
        color_array[R] = red[R] * percentage;
        color_array[G] = red[G] * percentage;
        color_array[B] = red[B] * percentage;
    } else if (color.equals("green")) {
        color_array[R] = green[R] * percentage;
        color_array[G] = green[G] * percentage;
        color_array[B] = green[B] * percentage;
    } else if (color.equals("blue")) {
        color_array[R] = blue[R] * percentage;
        color_array[G] = blue[G] * percentage;
        color_array[B] = blue[B] * percentage;
    } else if (color.equals("cyan")) {
        color_array[R] = cyan[R] * percentage;
        color_array[G] = cyan[G] * percentage;
        color_array[B] = cyan[B] * percentage;
    } else if (color.equals("magenta")) {
        color_array[R] = magenta[R] * percentage;
        color_array[G] = magenta[G] * percentage;
        color_array[B] = magenta[B] * percentage;
    } else if (color.equals("yellow")) {
        color_array[R] = yellow[R] * percentage;
        color_array[G] = yellow[G] * percentage;
        color_array[B] = yellow[B] * percentage;
    } else {
        rserial.println("color_array Not recognized...");
        return 0;
    }

    // Debug
    rserial.print("color_array[0] = "); rserial.println(color_array[0]);
    rserial.print("color_array[1] = "); rserial.println(color_array[1]);
    rserial.print("color_array[2] = "); rserial.println(color_array[2]);
    rserial.println("");

    setEveryPixelsColor(color_array);

    return 1;
}

int calculateStep(int prevValue, int endValue) 
{
    // What's the overall gap?
    int step = endValue - prevValue;
    // If its non-zero, divide by 1020
    if (step) {             
        step = 1020 / step;
    }
    
    return step;
}

int calculateVal(int step, int val, int i) 
{
    // If step is non-zero and its time to change a value,
    if ((step) && i % step == 0) {  
        if (step > 0) { // Increment the value if step is positive...
            val += 1;
        } else if (step < 0) { // Or decrement it if step is negative
            val -= 1;
        }
    }

    // Defensive driving: make sure val stays in the range 0-255
    if (val > 255) {
        val = 255;
    } else if (val < 0) {
        val = 0;
    }

    return val;
}

// Cross fade lighting 
void crossFade(int color[3], int wait) 
{
    int colorVal[3];

    // Convert to 0-255
    // int rVal = (color[R] * 255) / 100;
    // int gVal = (color[G] * 255) / 100;
    // int bVal = (color[B] * 255) / 100;
    int rVal = color[R];
    int gVal = color[G];
    int bVal = color[B];

    int stepR = calculateStep(currentcolor[R], rVal);
    int stepG = calculateStep(currentcolor[G], gVal);
    int stepB = calculateStep(currentcolor[B], bVal);

    for (int i = 0; i <= 1020; i++) {
        colorVal[R] = calculateVal(stepR, colorVal[R], i);
        colorVal[G] = calculateVal(stepG, colorVal[G], i);
        colorVal[B] = calculateVal(stepB, colorVal[B], i);

        setEveryPixelsColor(colorVal); 

        delay(wait);
    }

    setEveryPixelsColor(colorVal);
    delay(1);
} 

// Loop between red and green. 
// "wait" slows the Loop down.
int xmasloop(HardwareSerial &rserial, int wait)
{   
    rserial.println("**Made in to xmasloop**");
    rserial.print("wait = "); rserial.println(wait);
    rserial.println("");

    int color[3];

    setEveryPixelsColor(off);

    crossFade(red, wait);

    for (int i = 0; i < 3; i++) {
        crossFade(green, wait);
        crossFade(red, wait);
    }

    crossFade(off, wait);
   
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
