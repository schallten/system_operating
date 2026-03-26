// config_file.cpp
// Tonic Configuration (.tnc) Implementation

#include "config_file.h"
#include <Arduino.h>
#include <LittleFS.h>
#include "../core/output_handler.h"

const std::string fileLocation = "/home/config.tnc";

// Default Tonic configuration content
const char* DEFAULT_CONFIG = 
    "# Tonic Configuration (.tnc) v1.0\n"
    "# Declarative system configuration for System Operating\n"
    "\n"
    "system {\n"
    "    hostname = \"system-operating\";\n"
    "    version = \"1.0.0\";\n"
    "    graphics = \"1\";\n"
    "}\n"
    "\n"
    "network {\n"
    "    ssid = \"YourSSID\";\n"
    "    password = \"YourPassword\";\n"
    "    timeout = \"5000\";\n"
    "}\n"
    "\n"
    "display {\n"
    "    brightness = \"255\";\n"
    "    address = \"0x3C\";\n"
    "}\n";

bool isConfigPresent() {
    return LittleFS.exists(fileLocation.c_str());
}

bool generateDefaultConfig() {
    if (isConfigPresent()) {
        return false; // Already exists, do not overwrite
    }

    File configFile = LittleFS.open(fileLocation.c_str(), "w");
    if (!configFile) {
        printlnOutput("Error: Failed to create default config file");
        return false;
    }

    configFile.print(DEFAULT_CONFIG);
    configFile.close();
    printlnOutput("Tonic configuration (config.tnc) generated successfully.");
    return true;
}

bool validateConfig() {
    if (!isConfigPresent()) {
        return false;
    }

    File configFile = LittleFS.open(fileLocation.c_str(), "r");
    if (!configFile) {
        return false;
    }

    // Basic validation: ensure there's at least some structure
    // A robust parser would be needed for a full implementation
    bool hasBrackets = false;
    while (configFile.available()) {
        char c = configFile.read();
        if (c == '{' || c == '}') {
            hasBrackets = true;
            break;
        }
    }
    configFile.close();
    
    return hasBrackets;
}
