// init.h
// System initialization module - handles all startup routines

#ifndef INIT_H
#define INIT_H

#include <Arduino.h>

// Complete system initialization
void initializeSystem();

// Individual initialization functions
void initializeSerial();
void runBootSequence();

#endif
