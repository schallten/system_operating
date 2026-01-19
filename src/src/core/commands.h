// commands.h
// Command processing module - handles shell command parsing and execution

#ifndef COMMANDS_H
#define COMMANDS_H

#include <Arduino.h>

// Parse and execute a command
void parseCommand(const String &command);

// Display help message
void helpCommand();

// Execute a specific command by name
void executeCommand(const String &command);

#endif
