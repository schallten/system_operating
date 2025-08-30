#ifndef TIMEUNDWEATHER_H
#define TIMEUNDWEATHER_H

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

void getWeather(String city_code, String api_key);
void parseAndDisplayWeather(String response);
void getWeathDetails();

#endif