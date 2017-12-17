/**
 *  A script for an LED Ugly Sweater using the Arduino LilyPad 
 *  and a RN42 Bluetooth module.
**/

// Global Variables:
String command;

void parseCommand(HardwareSerial &rserial, String com)
{
    String part1;
    String part2;

    part1 = com.substring(0, com.indexOf("|"));
    part2 = com.substring(com.indexOf("|") + 1);

    rserial.println("===========================");

    rserial.print("Part 1 = ");
    rserial.println(part1);

    rserial.print("Part 2 = ");
    rserial.println(part2);
}

/**************************************************************************************************/

void setup() 
{
    Serial.begin(57600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.println("Serial Connected!");

    Serial.println("----------------------------------------------------");
}

void loop() 
{
    while (Serial.available()) {
        command += (char)Serial.read();
    }

    if (command.length()) {
        Serial.print("command=");
        Serial.print(command);
        Serial.print('\n');
        command = "";
    }

    delay(10);
}
