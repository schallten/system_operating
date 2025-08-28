// HEADER FILES CUSTOM
#include "src/display.h"  // Include the display functionality
#include "src/network.h"  // Include the network functionality
#include "src/monitor.h" // to get system stats
#include "src/shell.h" // to parse shell commands

// EXTERNAL AND BOARD LIBRARIES
#include <SPI.h>
#include <ESPping.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <FS.h>
#include <Wire.h>


void setup() {
  Serial.begin(9600);
  initializeDisplay();

  // Show the boot sequence
  displayBootSequence();

  // Show the "Welcome" message
  displayWelcomeMessage();

  displayText(getSystemStats().c_str()); // Show available resources

  delay(3000);

  // Call the network initialization function
  initializeNetwork();

  displayText("Initial setup complete");

  helpCommand();
  Serial.println("Setup complete.");
  
}

void loop() {
  // Nothing here for now, we just want the boot animation to run once
}
