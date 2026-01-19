// brainfuck compiler baby
#ifndef BF_H
#define BF_H

#include <Arduino.h>
#include <FS.h> 
#include <ESP8266WiFi.h>
#include <SPI.h>

void interpret(const char* program);
void runBFProgram();

#endif
