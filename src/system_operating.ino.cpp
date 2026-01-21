# 1 "/tmp/tmpdhig5hv2"
#include <Arduino.h>
# 1 "/home/poser/Documents/github_work/system_operating/src/system_operating.ino"

#include "src/core/config.h"
#include "src/core/init.h"
#include "src/core/shell.h"
void setup();
void loop();
#line 6 "/home/poser/Documents/github_work/system_operating/src/system_operating.ino"
void setup() {
  initializeSystem();

  helpCommand();
  Serial.println("Setup complete.");

  delay(SETUP_COMPLETE_DELAY);
  sendCommand();
}

void loop() {

}