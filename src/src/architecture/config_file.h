// file used to generate a central single config file ( will make a format for this ) that serves the same purpose as configuration.nix of nixos

#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <string>
#include <LittleFS.h>

std::string fileLocation = "/home/config.txt"; // called after filesystem is done

bool isConfigPresent();
bool generateDefaultConfig();
bool validateConfig();



#endif