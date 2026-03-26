// output_handler.cpp
// Output handler implementation - routes output to serial or display

//#define PC_VERSION // comment this out to disable pc version and use serial output instead

#include "output_handler.h"
#include "display.h"
#include <Arduino.h>
// Global graphics mode: 0 = serial, 1 = display, 2= cout ( if in case i make a pc version)
int graphics = 0;

#ifdef PC_VERSION // to turn it on define PC_VERSION in the build settings or at the top of this file
#include <iostream>
#endif

int graphics = 0;

void printOutput(const String &text) {
    if (graphics == 1) {
        displayText(text.c_str());
    }
#ifdef PC_VERSION
    else if (graphics == 2) {
        std::cout << text << std::endl;
    }
#endif
    else {
        Serial.print(text);
    }
}

void printOutput(const char* text) {
    if (graphics == 1) {
        displayText(text);
    }
#ifdef PC_VERSION
    else if (graphics == 2) {
        std::cout << text << std::endl;
    }
#endif
    else {
        Serial.print(text);
    }
}

void printlnOutput(const String &text) {
    if (graphics == 1) {
        displayText(text.c_str());
    }
#ifdef PC_VERSION
    else if (graphics == 2) {
        std::cout << text << std::endl;
    }
#endif
    else {
        Serial.println(text);
    }
}

void printlnOutput(const char* text) {
    if (graphics == 1) {
        displayText(text);
    }
#ifdef PC_VERSION
    else if (graphics == 2) {
        std::cout << text << std::endl;
    }
#endif
    else {
        Serial.println(text);
    }
}

void printCharOutput(char c) {
    if (graphics == 1) {
        String charStr(c);
        displayText(charStr.c_str());
    }
#ifdef PC_VERSION
    else if (graphics == 2) {
        std::cout << c << std::endl;
    }
#endif
    else {
        Serial.write(c);
    }
}
