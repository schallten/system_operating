// display.cpp
#include "display.h"
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Initialize the display
void initializeDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
}

// Universal display function
void universalDisplay(const char* text, int textSize, int xPos, int yPos, bool clearBefore, bool scroll, unsigned long scrollDelay, unsigned long displayDelay) {
  if (clearBefore) {
    display.clearDisplay();  // Optionally clear the screen before displaying new content
  }

  display.setTextSize(textSize);  // Set the desired text size
  display.setTextColor(WHITE);    // Set text color to white
  display.setCursor(xPos, yPos); // Set the cursor position

  // Check if scrolling is enabled
  if (scroll) {
    display.setTextSize(1);  // Set text size to 1 for smooth scrolling
    display.clearDisplay();  // Clear display before starting scroll
    display.setCursor(xPos, yPos);
    display.print(text);
    display.display();
    display.startscrollleft(0x00, 0x07);
    delay(scrollDelay);  // Scroll delay
    display.stopscroll();
  } else {
    display.println(text);  // Otherwise, just print the text
    display.display();  // Refresh the display
  }

  if (displayDelay > 0) {
    delay(displayDelay);  // Wait for specified time if a delay is set
  }
}


void displayText(const char* text) {
  // Default settings
  int defaultTextSize = 1;
  int defaultXPos = 0;
  int defaultYPos = 0;
  bool defaultClearBefore = true;
  bool defaultScroll = false;
  unsigned long defaultScrollDelay = 100;
  unsigned long defaultDisplayDelay = 0;

  // Call the existing universalDisplay function with the default settings
  universalDisplay(text, defaultTextSize, defaultXPos, defaultYPos, defaultClearBefore, defaultScroll, defaultScrollDelay, defaultDisplayDelay);
}

// Display the "SO__" boot screen with scrolling text and "loading..." below it
void displayBootSequence() {
  universalDisplay("System Operating", 1, 0, 0, true, true, 200, 500);
  universalDisplay("loading...", 1, 0, 36, true, false, 0, 2000);
}

// Display the "Welcome" message after boot
void displayWelcomeMessage() {
  universalDisplay("Welcome", 1, 0, 24, true, false, 0, 2000);
}
