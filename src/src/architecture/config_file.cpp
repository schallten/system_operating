// config_file.cpp
// Tonic Configuration (.tnc) Implementation

#include "config_file.h"
#include "../core/output_handler.h"
#include <Arduino.h>
#include <LittleFS.h>
#include <iostream>
#include <unordered_map>
#include <sstream> 
#include <string>
#include <string_view>

const std::string fileLocation = "/home/config.tnc";
const std::string known_labels[] = {"system", "network", "display"};
std::unordered_map<std::string, std::string> configValues;

// Default Tonic configuration content
const char *DEFAULT_CONFIG =
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

bool isConfigPresent() { return LittleFS.exists(fileLocation.c_str()); }

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

void labelHandler(File &configFile, const std::string &label) {
    std::string handler_content;
    std::string line;

    // Read lines until closing brace '}'
    while (configFile.available()) {
        line = configFile.readStringUntil('\n').c_str();

        // Remove leading/trailing spaces
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty() || line.rfind("#", 0) == 0) continue; // skip empty or comment lines

        if (line.find("}") != std::string::npos) break; // end of block

        handler_content += line + "\n";
    }

    // Parse handler_content line by line
    std::stringstream ss(handler_content);
    std::string curr_line;
    while (std::getline(ss, curr_line)) {
        size_t eq_pos = curr_line.find("=");
        if (eq_pos != std::string::npos) {
            std::string lhs = curr_line.substr(0, eq_pos);
            std::string rhs = curr_line.substr(eq_pos + 1);

            // Trim whitespace, quotes, and semicolons
            lhs.erase(0, lhs.find_first_not_of(" \t"));
            lhs.erase(lhs.find_last_not_of(" \t") + 1);

            rhs.erase(0, rhs.find_first_not_of(" \t\""));
            rhs.erase(rhs.find_last_not_of(" \t\";") + 1);

            configValues[lhs] = rhs;
        }
    }
}

void readConfig() {
    if (!validateConfig()) {
        printlnOutput("Invalid config file.");
        return;
    }

    File configFile = LittleFS.open(fileLocation.c_str(), "r");
    if (!configFile) return;

    std::string line;
    while (configFile.available()) {
        line = configFile.readStringUntil('\n').c_str();
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty() || line.rfind("#", 0) == 0) continue;

        for (const std::string &label : known_labels) {
            if (line.find(label) == 0 && line.find("{") != std::string::npos) {
                labelHandler(configFile, label);
            }
        }
    }
    configFile.close();

    // print each entry
    for (const auto &pair : configValues) {
        printlnOutput(String(pair.first.c_str()) + " = " + String(pair.second.c_str()));
    }

    printlnOutput("\t\t\t\t\t\t\t");
    printlnOutput("config file loaded successfully");
}