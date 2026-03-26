// output_handler.cpp
// Output handler implementation - routes output to serial or display

#include "output_handler.h"
#include "display.h"
#include <Arduino.h>

// Global graphics mode: 0 = serial, 1 = display
int graphics = 1;

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
        // In graphics mode, we let the display handler handle the newline logic
        // but we add it if it's not there to ensure we move to next line
        if (text.endsWith("\n")) {
            displayText(text.c_str());
        } else {
            String withNewline = text + "\n";
            displayText(withNewline.c_str());
        }
    } else {
        Serial.println(text);
    }
}

void printlnOutput(const char* text) {
    if (graphics == 1) {
        String t = String(text);
        if (t.endsWith("\n")) {
            displayText(text);
        } else {
            String withNewline = t + "\n";
            displayText(withNewline.c_str());
        }
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
