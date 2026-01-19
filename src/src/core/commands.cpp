// commands.cpp
// Command processing implementation

#include "commands.h"
#include "config.h"
#include "network.h"
#include "display.h"
#include "monitor.h"
#include "../extras/timeundweather.h"
#include "../extras/bf.h"
#include <Arduino.h>

void helpCommand() {
    displayText("Available commands: \n help: shows this message \n ctrl_c: stop current running program and return to shell \n stats: shows system stats \n wifi: shows wifi status \n weather : display weather (needs credentials) \n bf: run brainfuck code");
}

void executeCommand(const String &command) {
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
    } else {
        displayText("Unknown command. Type 'help' for a list of commands.");
    }
}

void parseCommand(const String &command) {
    if (command == "quit") {
        displayText("Exiting shell mode...");
        Serial.println("Exiting shell mode...");
        return;
    }
    
    executeCommand(command);
}
