#include "shell.h"
#include "network.h"
#include "display.h"
#include "monitor.h"
#include "timeundweather.h"
#include "bf.h"

#include <Arduino.h>
#include <FS.h> 
#include <ESP8266WiFi.h>
#include <SPI.h>

/*
Since we are limited on memory, the shell currently has very few commands. Of course, it's extensible in the future.
*/

bool lastCommandWasQ = false;

void helpCommand() {
    displayText("Available commands: \n help: shows this message \n ctrl_c: stop current running program and return to shell \n stats: shows system stats \n wifi: shows wifi status \n weather : display weather (needs credentials) \n bf: run brainfuck code");
}

void parseCommand(const String &command) {
    if (command == "help") {
        helpCommand();
    } else if (command == "stats") {
        displayText(getSystemStats().c_str());
    } else if (command == "wifi") {
        displayText(getWiFiStatus().c_str());
    } else if (command == "weather") {
        getWeathDetails();
    } else if (command == "bf") {
        runBFProgram();
    } else if (command == "ctrl_c") {
        displayText("No program is currently running.");
        delay(2000);
        displayText("This feature is under works");
        Serial.println("This feature is under works, when in future versions proper multitasking is employed you will be able to stop running programs");
    } else if (command == "quit") {
        displayText("Exiting shell mode...");
        Serial.println("Exiting shell mode...");
        return;  // Exit the loop when 'quit' command is received
    } else {
        displayText("Unknown command. Type 'help' for a list of commands.");
    }
}

void sendCommand() {
    displayText("You are now in the shell\nLook at serial monitor for input\nFirst press 'q' to exit display mode");
    Serial.println("You are now in the shell. First press 'q' to exit display mode, then enter your command.");
    
    // Continuously loop until 'quit' is entered
    while (true) {
        if (Serial.available() > 0) {
            String command = Serial.readStringUntil('\n');
            command.trim();

            if (command == "q") {
                lastCommandWasQ = true;  // User pressed 'q', wait for next command
                displayText("Waiting for next command...");
            } else if (command == "n" || command == "p") {
                // Do nothing if command is 'n' or 'p'
            } else if (lastCommandWasQ) {
                // If the last command was 'q', treat the next input as a valid command
                lastCommandWasQ = false;  // Reset the flag after receiving the command
                parseCommand(command);  // Process the next valid command
            } else {
                displayText("Please enter 'q' first before entering a command.");
            }

            // If the command is 'quit', break out of the loop to exit the shell
            if (command == "quit") {
                break;
            }
        }
    }
}
