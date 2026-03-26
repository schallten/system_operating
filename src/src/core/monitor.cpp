// monitor.cpp
#include "monitor.h"
#include "display.h"

#include <Arduino.h>    // Necessary for String and other Arduino functions
#include <LittleFS.h>   // For LittleFS filesystem
#include <ESP8266WiFi.h> // If you are using WiFi functions

// Function to return system stats
String getSystemStats() {
  // Free heap memory in bytes
  unsigned int freeHeap = ESP.getFreeHeap();

  // Total flash memory size and free flash space
  unsigned int flashSize = ESP.getFlashChipSize();
  unsigned int freeSketchSpace = ESP.getFreeSketchSpace();

  // LittleFS storage stats
  FSInfo fsInfo;
  LittleFS.info(fsInfo);
  unsigned int totalLittleFS = fsInfo.totalBytes;
  unsigned int usedLittleFS = fsInfo.usedBytes;
  unsigned int freeLittleFS = totalLittleFS - usedLittleFS;

  // Construct a string with all the stats
  String stats = "System Stats:\n";
  stats += "Free Heap: " + String(freeHeap) + " bytes\n";
  stats += "Flash Size: " + String(flashSize) + " bytes\n";
  stats += "Free Flash Space: " + String(freeSketchSpace) + " bytes\n";
  stats += "Free LittleFS Space: " + String(freeLittleFS) + " bytes\n";

  return stats;
}
