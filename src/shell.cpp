#include "shell.h"
#include "network.h"
#include "display.h"
#include "monitor.h"


#include <Arduino.h>
#include <FS.h> 
#include <ESP8266WiFi.h>
#include <SPI.h>

/*
Since we are limited on memory , the shell currently has very few commands. Ofcourse its extensible in the future
*/

void helpCommand(){
    displayText("Available commands: \n help: shows this message \n stats: shows system stats \n wifi: shows wifi status \n more check \n one more line \n one more line for testing");
}

void parseCommand(const String &command) {
    if (command == "help"){
        helpCommand();
    }
}

void parseShellCommand(const char* command) {
    // Example: just echo the command for now
    Serial.print("Received command: ");
    Serial.println(command);
    // Add actual command handling logic here
}
