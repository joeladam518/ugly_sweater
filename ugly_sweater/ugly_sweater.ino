/**
 *  A script for an LED Ugly Sweater using the Arduino LilyPad 
 *  and a RN42 Bluetooth module.
**/

#include <Adafruit_NeoPixel.h>

// Pins:

static const int NEO_PIN1 = 7;
static const int NEO_PIN2 = 9;
static const int NEO_PIN3 = 11;

// Global Variables:

// To hold commands coming in through serial.
String command;

// LED Color Pin Enum
static const int R = 0;
static const int G = 1;
static const int B = 2;

// Number of neopixels
static const int NUM_NEOPIXELS = 2;

// Initialize the NeoPixel Object // NEO_KHZ400
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUM_NEOPIXELS, NEO_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUM_NEOPIXELS, NEO_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3 = Adafruit_NeoPixel(NUM_NEOPIXELS, NEO_PIN3, NEO_GRB + NEO_KHZ800);

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

// Convert separate R,G,B into packed 32-bit RGB color.
// Packed format is always RGB, regardless of LED strand color order.
uint32_t neoPixelColor(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

void setEveryPixelsColor(int color[3]) 
{
    for (int i = 0; i < NUM_NEOPIXELS; i++) {
        // This sends the updated pixel color to the hardware.
        pixels1.setPixelColor(i, neoPixelColor(color[R], color[G], color[B]));
        pixels1.show();
        pixels2.setPixelColor(i, neoPixelColor(color[R], color[G], color[B]));
        pixels2.show(); 
        pixels3.setPixelColor(i, neoPixelColor(color[R], color[G], color[B]));
        pixels3.show();  
    }

    currentcolor[R] = color[R];
    currentcolor[G] = color[G];
    currentcolor[B] = color[B];
}

// Set the color by given name.
// TODO: Should I just set the values directly with and array?
int setColor(HardwareSerial &rserial, String color, float percentage)
{   
    rserial.println("**Made in to setColor**");
    rserial.print("color = "); rserial.println(color);
    rserial.print("percentage = "); rserial.println(percentage);
    rserial.println("");

    int color_array[3];

    // Defensive driving
    if (percentage > 1) {
        percentage = 1;
    }
    if (percentage < 0) {
        percentage = 0;
    }

    if (color.equals("off")) {
        color_array[R] = off[R];
        color_array[G] = off[G];
        color_array[B] = off[B];
    } else if (color.equals("on")) {
        color_array[R] = on[R] * percentage;
        color_array[G] = on[G] * percentage;
        color_array[B] = on[B] * percentage;
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

//Theatre-style crawling lights.
void theatreChase(uint32_t c, uint8_t wait) {
    for (int j = 0; j < 10; j++) {  // do 10 cycles of chasing
        for (int q = 0; q < NUM_NEOPIXELS; q++) {
            for (uint16_t i = 0; i < NUM_NEOPIXELS; i = i + NUM_NEOPIXELS) {
                pixels1.setPixelColor(i+q, c); //turn every third pixel on
                pixels2.setPixelColor(i+q, c); //turn every third pixel on
                pixels3.setPixelColor(i+q, c); //turn every third pixel on
            }
            pixels1.show();
            pixels2.show();
            pixels3.show();

            delay(wait);

            for (uint16_t i = 0; i < NUM_NEOPIXELS; i = i + 3) {
                pixels1.setPixelColor(i+q, 0); //turn every third pixel off
                pixels2.setPixelColor(i+q, 0); //turn every third pixel off
                pixels3.setPixelColor(i+q, 0); //turn every third pixel off
            }
        }
    }
}

// Loop between red and green. 
// "wait" slows the Loop down.
int xmasloop(HardwareSerial &rserial, int wait)
{   
    rserial.println("**Made in to xmasloop**");
    rserial.print("wait = "); rserial.println(wait);
    rserial.println("");

    for (int i = 0; i < 5; i++){
       theatreChase(neoPixelColor(127, 0, 0), wait);   // Red
       theatreChase(neoPixelColor(0, 127, 0), wait);   // Green
    }

    delay(1000);

    setEveryPixelsColor(off);

    return 1;
}

// Parses the incoming command for what to do...
// Command examples:
//     setcolor|color@percentage
//     xmasloop|delay
int parseCommand(HardwareSerial &rserial, String com)
{
    String part1;
    String part2;

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
            
            return setColor(rserial, inputColor, percentage);
        } else {
            inputColor = part2;
            return setColor(rserial, inputColor, 1);
        }
    } else if (part1.equals("xmasloop")) {
        int wait = part2.toInt();
        return xmasloop(rserial, wait);
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

    // Initializes the NeoPixels
    pixels1.begin();
    pixels2.begin();
    pixels3.begin();

    setEveryPixelsColor(off);
}

void loop() {
    if (Serial.available()) {
        char ch = Serial.read();

        // Debug
        //Serial.print("-"); Serial.print(ch); Serial.print("-");
        
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
