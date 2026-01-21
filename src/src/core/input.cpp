// input.cpp
// User input handling implementation

#include "input.h"
#include "config.h"
#include "shell.h"
#include "display.h"
#include "output_handler.h"
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
        printlnOutput("Waiting for next command...");
    } else if (command == "n" || command == "p") {
        // Display navigation flags - do nothing (handled by display)
    } else if (lastCommandWasQ) {
        lastCommandWasQ = false;
        parseCommand(command);
    } else {
        printlnOutput("Please enter 'q' first before entering a command.");
    }
}

void sendCommand() {
    printlnOutput("You are now in the shell\nLook at serial monitor for input\nFirst press 'q' to exit display mode");
    printlnOutput("You are now in the shell. First press 'q' to exit display mode, then enter your command.");
    
    while (true) {
        processShellInput();
        
        // Check for quit command
        String command = readCommand();
        if (command == "quit") {
            break;
        }
    }
}
