// display.h
#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

// Initialize the OLED display
void initializeDisplay();

// Main text display function - auto-scrolls if text is too long
void displayText(const char* text);

// Universal display function with full control
void universalDisplay(const char* text, int textSize, int xPos, int yPos, bool clearBefore = true, bool scroll = false, unsigned long scrollDelay = 100, unsigned long displayDelay = 0);

// Display static text without scrolling
void displayStaticText(const char* text, int textSize = 1, int xPos = 0, int yPos = 0);

// Utility functions for text measurement
int calculateTextWidth(const char* text, int textSize);
int calculateTextLines(const char* text, int textSize);
bool textNeedsScrolling(const char* text, int textSize);

// Boot sequence and welcome functions

int countLines(const char* text);
void displayBootSequence();
void displayPage(String lines[], int lineCount, int maxLines, int page, int totalPages);
void displayWelcomeMessage();

#endif