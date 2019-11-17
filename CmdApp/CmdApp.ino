#include "CmdMap.h"

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
char buf[64] = {};

void setup() {
  Serial.begin(9600);
  delay(1);
  Serial.println("Start");
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    // Serial.println(inputString);
    inputString.toCharArray(buf, 64);
    HandleCmd(buf);
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      break;
    }
    // add it to the inputString:
    inputString += inChar;
  }
}
