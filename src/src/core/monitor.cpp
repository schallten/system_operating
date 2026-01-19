// monitor.cpp
#include "monitor.h"
#include "display.h"

#include <Arduino.h>    // Necessary for String and other Arduino functions
#include <FS.h>          // For SPIFFS filesystem
#include <ESP8266WiFi.h> // If you are using WiFi functions

// Function to return system stats
String getSystemStats() {
  // Free heap memory in bytes
  unsigned int freeHeap = ESP.getFreeHeap();

  // Total flash memory size and free flash space
  unsigned int flashSize = ESP.getFlashChipSize();
  unsigned int freeSketchSpace = ESP.getFreeSketchSpace();

  // SPIFFS storage stats
  FSInfo fsInfo;
  SPIFFS.info(fsInfo);
  unsigned int freeSpiffs = fsInfo.totalBytes - fsInfo.usedBytes;

  // Construct a string with all the stats
  String stats = "System Stats:\n";
  stats += "Free Heap: " + String(freeHeap) + " bytes\n";
  stats += "Flash Size: " + String(flashSize) + " bytes\n";
  stats += "Free Flash Space: " + String(freeSketchSpace) + " bytes\n";
  stats += "Free SPIFFS Space: " + String(freeSpiffs) + " bytes\n";

  return stats;
}
