// output_handler.cpp
// Output handler implementation - routes output to serial or display

#include "output_handler.h"
#include "display.h"
#include <Arduino.h>

// Global graphics mode: 0 = serial, 1 = display
int graphics = 0;

void printOutput(const String &text) {
    if (graphics == 1) {
        displayText(text.c_str());
    } else {
        Serial.print(text);
    }
}

void printOutput(const char* text) {
    if (graphics == 1) {
        displayText(text);
    } else {
        Serial.print(text);
    }
}

void printlnOutput(const String &text) {
    if (graphics == 1) {
        displayText(text.c_str());
    } else {
        Serial.println(text);
    }
}

void printlnOutput(const char* text) {
    if (graphics == 1) {
        displayText(text);
    } else {
        Serial.println(text);
    }
}

void printCharOutput(char c) {
    if (graphics == 1) {
        String charStr(c);
        displayText(charStr.c_str());
    } else {
        Serial.write(c);
    }
}
