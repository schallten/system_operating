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
