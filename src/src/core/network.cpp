// network.cpp
#include "network.h"
#include <ESP8266WiFi.h>
#include <ESPping.h>   // Include the ESPping library
#include <ESP8266HTTPClient.h>
#include "display.h"
#include "config.h"
#include "output_handler.h"

void initializeConnection(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    printlnOutput("Connecting to Wifi...");
    unsigned long startMillis = millis();
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        printOutput(".");
        
        if (millis() - startMillis >= CONNECTION_TIMEOUT) {
            printlnOutput("Connection timed out.");
            printlnOutput("Connection timed out.");
            return;
        }
    }
    
    // Once connected, print the local IP address
    IPAddress localIP = WiFi.localIP();
    String localIPStr = localIP.toString();  // Convert to String
    printOutput("Local IP: ");
    printlnOutput(localIP.toString().c_str());
    printlnOutput(localIPStr.c_str());  // Display local IP as const char*

    printlnOutput("Connected to Wifi");
    printlnOutput("Connected to Wifi");
}

void initializeNetwork() {
    printlnOutput("Network Setup");
    printlnOutput("\nNetwork Setup");
    
    while(Serial.available()) { // Clear any leftover serial data
        Serial.read();
    }
    
    printlnOutput("Enter WiFi SSID:");
    while(!Serial.available()) { delay(100); }
    String ssid = Serial.readStringUntil('\n');
    ssid.trim();
    
    // Clear buffer again
    while(Serial.available()) {
        Serial.read();
    }
    delay(100); // Small delay to ensure buffer is clear
    
    printlnOutput("Enter WiFi password:");
    while(!Serial.available()) { delay(100); }
    String password = Serial.readStringUntil('\n');
    password.trim();
    
    printlnOutput("Connecting to WiFi...");
    printlnOutput("Connecting to WiFi...");
    
    WiFi.begin(ssid.c_str(), password.c_str());
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        printOutput(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        String connectedMsg = "Connected to WiFi\nIP: " + WiFi.localIP().toString();
        printlnOutput("\n" + connectedMsg);
        printlnOutput(connectedMsg.c_str());
    } else {
        String failMsg = "Failed to connect to WiFi";
        printlnOutput("\n" + failMsg);
        printlnOutput(failMsg.c_str());
    }
}

bool checkConnection() {
    IPAddress targetIP;
    
    // Check WiFi status
    if (WiFi.status() != WL_CONNECTED) {
        printlnOutput("WiFi not connected");
        printlnOutput("WiFi not connected");
        return false;
    }
    
    // Try to resolve the server IP address (Google)
    if (WiFi.hostByName(PING_SERVER_HOST, targetIP)) {
        // Display the resolved IP address
        String targetIPStr = targetIP.toString();  // Convert IP to String
        printlnOutput("DNS resolved: " + targetIPStr);
        printlnOutput(targetIPStr.c_str());  // Display IP address as const char*
        
        // Ping using ESPping library
        if (Ping.ping(targetIP, 3)) { // Ping target 3 times
            printlnOutput("Ping successful!");
            return true;
        } else {
            printlnOutput("Ping failed.");
            return false;
        }
    } else {
        printlnOutput("DNS resolution failed.");
        printlnOutput("DNS resolution failed.");
        return false;
    }
}

bool httpCheckConnection() {
    const char* server_url = "http://www.google.com";  // Or any reliable server URL
    
    // Use HTTPClient to make an HTTP request for connection validation
    HTTPClient http;
    WiFiClient client;
    http.begin(client, server_url);
    
    int httpCode = http.GET();
    
    if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
            printlnOutput("HTTP Connection is active");
            printlnOutput("HTTP Connection is active");
            return true;
        } else {
            printlnOutput("Unexpected HTTP code");
            printlnOutput("Unexpected HTTP code");
            return false;
        }
    } else {
        printlnOutput("HTTP GET failed");
        printlnOutput("HTTP GET failed");
        return false;
    }
}

String getWiFiStatus() {
    String status = "WiFi Status:\n";
    
    if (WiFi.status() == WL_CONNECTED) {
        status += "Connected\n";
        status += "SSID: " + WiFi.SSID() + "\n";
        status += "IP: " + WiFi.localIP().toString() + "\n";
        status += "Signal: " + String(WiFi.RSSI()) + " dBm";
    } else {
        status += "Disconnected";
    }
    
    return status;
}
