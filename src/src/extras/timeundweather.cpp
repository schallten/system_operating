// timeundweather.cpp
#include "timeundweather.h"
#include "../core/display.h"
#include "../core/network.h"
#include "../core/output_handler.h"

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>


void getWeather(String city_code, String api_key) {
    const char server[] = "api.openweathermap.org";
    WiFiClient client;
    
    String url = "/data/2.5/forecast?q=" + city_code + "&APPID=" + api_key + "&mode=json&units=metric&cnt=2";
    
    if (client.connect(server, 80)) {
        client.println("GET " + url + " HTTP/1.1");
        client.println("Host: api.openweathermap.org");
        client.println("Connection: close");
        client.println();
        
        String response = "";
        while (client.available()) {
            response += (char)client.read();
        }
        parseAndDisplayWeather(response);
    }
}

void parseAndDisplayWeather(String response) {
    int tempStart = response.indexOf("\"temp\":") + 7;
    int tempEnd = response.indexOf(",", tempStart);
    String currentTemp = response.substring(tempStart, tempEnd);

    tempStart = response.indexOf("\"temp\":", tempEnd) + 7;
    tempEnd = response.indexOf(",", tempStart);
    String predictedTemp = response.substring(tempStart, tempEnd);

    String output = "Current Temp: " + currentTemp + "°C\nPredicted Temp: " + predictedTemp + "°C";
    printlnOutput(output.c_str());
}


void getWeathDetails(){
    printlnOutput("Enter city code and api key in serial monitor");
    printlnOutput("Enter city code and api key in serial monitor");
    if (Serial.available() > 0){
        printlnOutput("......");
        printlnOutput("Enter city code and country (eg: London,GB)");
        String citycode = Serial.readStringUntil('\n');
        citycode.trim();
        printlnOutput("......");
        printlnOutput("Enter openweather api key : ");
        String apiKey = Serial.readStringUntil('\n');
        apiKey.trim();
        printlnOutput("-- Passing values --");
        getWeather(citycode, apiKey);
    }
}
