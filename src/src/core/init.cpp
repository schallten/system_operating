// init.cpp
// System initialization implementation

#include "init.h"
#include "config.h"
#include "display.h"
#include "network.h"
#include "monitor.h"
#include <Arduino.h>

void initializeSerial() {
    Serial.begin(SERIAL_BAUD);
    delay(100);  // Wait for serial to stabilize
}

void runBootSequence() {
    // Show the boot sequence
    displayBootSequence();

    // Show the "Welcome" message
    displayWelcomeMessage();

    // Display available resources
    displayText(getSystemStats().c_str());

    delay(BOOT_DISPLAY_DELAY);
}

void initializeSystem() {
    // Initialize serial communication
    initializeSerial();
    
    // Initialize display
    initializeDisplay();

    // Run boot sequence
    runBootSequence();

    // Initialize network
    initializeNetwork();

    // Display completion message
    displayText("Initial setup complete");
    delay(SETUP_COMPLETE_DELAY);
}
