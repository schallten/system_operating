#ifndef MONITOR_H
#define MONITOR_H

#include <Arduino.h>  // This ensures the String class is available
#include <FS.h>        // For SPIFFS
#include <ESP8266WiFi.h> // If using WiFi functionality

String getSystemStats();  // Declare the function

#endif
