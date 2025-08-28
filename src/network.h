// manages the network part of the os , currently supports only wpa2 personal
#ifndef NETWORK_H
#define NETWORK_H

#include <ESP8266WiFi.h>
#include <ESPping.h>

void initializeConnection(const char* ssid,const char* password);
bool checkConnection();
void initializeNetwork();

#endif