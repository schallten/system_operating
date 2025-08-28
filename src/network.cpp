#include "network.h"
#include <ESP8266WiFi.h>
#include <ESPping.h>   // Include the ESPping library
#include <ESP8266HTTPClient.h>
#include "display.h"

// Timeout period for connection check (in milliseconds)
#define CONNECTION_TIMEOUT 5000
#define MAX_RETRIES 3

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
  displayText("Initializing Network...");
  String ssid = "", password = "";

  // Check network connection
  if (!checkConnection()) {
    displayText("Could not connect");
    delay(2000);
    displayText("Serial monitor baud 9600 for entry");
    
    // Ask for SSID and password via serial monitor
    while (ssid == "") {
      if (Serial.available()) {
        displayText("Enter SSID:");
        Serial.println("Enter SSID: ");
        ssid = Serial.readStringUntil('\n');
        ssid.trim();
        
        Serial.println("Enter password for " + ssid + ":");
        
        while (password == "") {
          if (Serial.available()) {
            password = Serial.readStringUntil('\n');
            password.trim();
          }
        }
      }
    }
  }

  // Initialize the connection with SSID and password
  initializeConnection(ssid.c_str(), password.c_str());

  // Check if the connection was successful
  if (checkConnection()) {
    displayText("Network Initialized");
  } else {
    displayText("Network Init Failed");
  }

  delay(2000);
  displayText("Network setup complete");
}


bool checkConnection() {
    const char* server_host = "8.8.8.8";  // Google's DNS server
    IPAddress targetIP;
    
    // Check WiFi status
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi not connected");
        displayText("WiFi not connected");
        return false;
    }
    
    // Try to resolve the server IP address (Google)
    if (WiFi.hostByName(server_host, targetIP)) {
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
