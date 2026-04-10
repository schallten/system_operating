// file used to generate a central single config file ( will make a format for this ) that serves the same purpose as configuration.nix of nixos

#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <string>
#include <LittleFS.h>
#include <unordered_map>

extern const std::string fileLocation;

// map to store all config values in memory ( example: ssid -> "yourSSID") (acessible in whole os)
extern std::unordered_map<std::string, std::string> configValues;

bool isConfigPresent();
bool generateDefaultConfig();
bool validateConfig();
// reader function ( to run on boot and updates , populates the configValues map)
void readConfig();

#endif