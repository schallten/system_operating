// shell.h
#ifndef SHELL_H
#define SHELL_H

#include <Arduino.h>
#include <FS.h> 
#include <ESP8266WiFi.h>
#include <SPI.h>

void parseCommand(const String &command);
void helpCommand();
void sendCommand();

#endif
