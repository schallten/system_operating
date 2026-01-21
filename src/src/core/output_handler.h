// output_handler.h
// Output handler module - routes output to serial or display based on graphics setting

#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H

#include <Arduino.h>

// Global graphics mode variable: 0 = serial only, 1 = display text
extern int graphics;

// Output a string based on graphics mode
void printOutput(const String &text);
void printOutput(const char* text);

// Output a string with newline
void printlnOutput(const String &text);
void printlnOutput(const char* text);

// Output a single character
void printCharOutput(char c);

#endif
