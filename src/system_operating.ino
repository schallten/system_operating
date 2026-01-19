// HEADER FILES CUSTOM - CORE MODULES
#include "src/core/config.h"    // Include configuration constants
#include "src/core/init.h"      // Include system initialization
#include "src/core/shell.h"     // Include shell functionality

void setup() {
  initializeSystem();  // Run complete system initialization
  
  helpCommand();
  Serial.println("Setup complete.");

  delay(SETUP_COMPLETE_DELAY);
  sendCommand(); // shell entry
}

void loop() {
  // Nothing here for now, we just want the boot animation to run once
}
