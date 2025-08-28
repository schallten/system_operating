// display.h
#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

void initializeDisplay();
void universalDisplay(const char* text, int textSize, int xPos, int yPos, bool clearBefore = true, bool scroll = false, unsigned long scrollDelay = 100, unsigned long displayDelay = 0);

void displayBootSequence();
void displayText(const char* text);
void displayWelcomeMessage();

#endif
