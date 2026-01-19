// input.cpp
// User input handling implementation

#include "input.h"
#include "config.h"
#include "commands.h"
#include "display.h"
#include <Arduino.h>

static bool lastCommandWasQ = false;

String readCommand() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        return input;
    }
    return "";
}

void processShellInput() {
    String command = readCommand();
    
    if (command.isEmpty()) {
        return;
    }
    
    if (command == "q") {
        lastCommandWasQ = true;
        displayText("Waiting for next command...");
    } else if (command == "n" || command == "p") {
        // Display navigation flags - do nothing (handled by display)
    } else if (lastCommandWasQ) {
        lastCommandWasQ = false;
        parseCommand(command);
    } else {
        displayText("Please enter 'q' first before entering a command.");
    }
}

void sendCommand() {
    displayText("You are now in the shell\nLook at serial monitor for input\nFirst press 'q' to exit display mode");
    Serial.println("You are now in the shell. First press 'q' to exit display mode, then enter your command.");
    
    while (true) {
        processShellInput();
        
        // Check for quit command
        String command = readCommand();
        if (command == "quit") {
            break;
        }
    }
}
