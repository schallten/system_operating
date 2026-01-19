// shell.cpp
// Legacy shell module - delegates to input and commands modules

#include "shell.h"
#include "input.h"
#include "commands.h"

void helpCommand() {
    ::helpCommand();  // Delegate to commands module
}

void parseCommand(const String &command) {
    ::parseCommand(command);  // Delegate to commands module
}

void sendCommand() {
    ::sendCommand();  // Delegate to input module
}
