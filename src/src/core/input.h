// input.h
// User input handling module - manages serial input and shell interaction

#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>

// Main shell entry point - reads and processes user commands
void sendCommand();

// Read a command from serial input
String readCommand();

// Handle shell input with mode flags
void processShellInput();

#endif
