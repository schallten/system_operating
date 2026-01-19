// network.cpp
#include "network.h"
#include <ESP8266WiFi.h>
#include <ESPping.h>   // Include the ESPping library
#include <ESP8266HTTPClient.h>
#include "display.h"
#include "config.h"

void initializeConnection(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    displayText("Connecting to Wifi...");
    unsigned long startMillis = millis();
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        
        if (millis() - startMillis >= CONNECTION_TIMEOUT) {
            Serial.println("Connection timed out.");
            displayText("Connection timed out.");
            return;
        }
    }
    
    // Once connected, print the local IP address
    IPAddress localIP = WiFi.localIP();
    String localIPStr = localIP.toString();  // Convert to String
    Serial.print("Local IP: ");
    Serial.println(localIP);
    displayText(localIPStr.c_str());  // Display local IP as const char*

    displayText("Connected to Wifi");
    Serial.println("Connected to Wifi");
}

void initializeNetwork() {
    displayText("Network Setup");
    Serial.println("\nNetwork Setup");
    
    while(Serial.available()) { // Clear any leftover serial data
        Serial.read();
    }
    
    Serial.println("Enter WiFi SSID:");
    while(!Serial.available()) { delay(100); }
    String ssid = Serial.readStringUntil('\n');
    ssid.trim();
    
    // Clear buffer again
    while(Serial.available()) {
        Serial.read();
    }
    delay(100); // Small delay to ensure buffer is clear
    
    Serial.println("Enter WiFi password:");
    while(!Serial.available()) { delay(100); }
    String password = Serial.readStringUntil('\n');
    password.trim();
    
    Serial.println("Connecting to WiFi...");
    displayText("Connecting to WiFi...");
    
    WiFi.begin(ssid.c_str(), password.c_str());
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        String connectedMsg = "Connected to WiFi\nIP: " + WiFi.localIP().toString();
        Serial.println("\n" + connectedMsg);
        displayText(connectedMsg.c_str());
    } else {
        String failMsg = "Failed to connect to WiFi";
        Serial.println("\n" + failMsg);
        displayText(failMsg.c_str());
    }
}

bool checkConnection() {
    IPAddress targetIP;
    
    // Check WiFi status
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi not connected");
        displayText("WiFi not connected");
        return false;
    }
    
    // Try to resolve the server IP address (Google)
    if (WiFi.hostByName(PING_SERVER_HOST, targetIP)) {
        // Display the resolved IP address
        String targetIPStr = targetIP.toString();  // Convert IP to String
        Serial.println("DNS resolved: " + targetIPStr);
        displayText(targetIPStr.c_str());  // Display IP address as const char*
        
        // Ping using ESPping library
        if (Ping.ping(targetIP, 3)) { // Ping target 3 times
            Serial.println("Ping successful!");
            return true;
        } else {
            Serial.println("Ping failed.");
            return false;
        }
    } else {
        Serial.println("DNS resolution failed.");
        displayText("DNS resolution failed.");
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
            Serial.println("HTTP Connection is active");
            displayText("HTTP Connection is active");
            return true;
        } else {
            Serial.printf("Unexpected HTTP code: %d\n", httpCode);
            displayText("Unexpected HTTP code");
            return false;
        }
    } else {
        Serial.printf("HTTP GET failed, error: %s\n", http.errorToString(httpCode).c_str());
        displayText("HTTP GET failed");
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
