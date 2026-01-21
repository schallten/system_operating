// shell.cpp
// Shell command parsing and handling

#include "shell.h"
#include "config.h"
#include "display.h"
#include "commands.h"
#include "output_handler.h"
#include <Arduino.h>

void helpCommand() {
    printlnOutput("Available commands: \n help: shows this message \n ctrl_c: stop current running program and return to shell \n stats: shows system stats \n wifi: shows wifi status \n weather : display weather (needs credentials) \n bf: run brainfuck code");
}

void parseCommand(const String &command) {
    if (command == "quit") {
        printlnOutput("Exiting shell mode...");
        return;
    }
    
    executeCommand(command);
}

void sendCommand(){
    printlnOutput("welcome to the shell");
    printlnOutput("Type 'help' to see available commands.");
    while (true) {
        printlnOutput("Enter command:");
        while (Serial.available() == 0) {
            delay(100); // wait for user input
        }
        String command = Serial.readStringUntil('\n');
        command.trim();
        
        parseCommand(command);
    }
}
