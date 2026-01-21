// init.cpp
// System initialization implementation

#include "init.h"
#include "config.h"
#include "display.h"
#include "network.h"
#include "monitor.h"
#include "output_handler.h"
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
    // printlnOutput(getSystemStats().c_str()); removing cuz neededd really as i will shift to memory allocation on the go instead of pre allocation
    printlnOutput("Boot sequence complete");

    delay(BOOT_DISPLAY_DELAY); 
}

void initializeSystem() {
    // Initialize serial communication
    initializeSerial();
    
    // Initialize display
    if (graphics == 1){
        initializeDisplay();
    }else{
        printlnOutput("Graphics mode disabled, skipping display initialization.");
    }

    // Run boot sequence
    runBootSequence();

    // Initialize network
    // initializeNetwork(); will switch to manual wifi allotment just in case user wants offline work too

    // Display completion message
    printlnOutput("Initial setup complete");
    delay(SETUP_COMPLETE_DELAY);
}
