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
    display.display();
}


// Helper function to count lines in text (including newlines)
int countLines(const char* text) {
    int lines = 1; // Start with 1 line
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n') {
            lines++;
        }
    }
    return lines;
}

// Function to display a specific page
void displayPage(String lines[], int lineCount, int maxLines, int page, int totalPages) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    
    int startLine = page * maxLines;
    int endLine = min(startLine + maxLines, lineCount);
    
    // Display the lines for this page
    for (int i = startLine; i < endLine; i++) {
        // Trim line if it's too long (shouldn't happen but just in case)
        String displayLine = lines[i];
        if (displayLine.length() > 21) { // 128/6 = 21 chars per line
            displayLine = displayLine.substring(0, 21);
        }
        display.println(displayLine);
    }
    
    // Show page indicator and navigation help in bottom right
    display.setCursor(90, 56);
    display.printf("%d/%d", page + 1, totalPages);
    
    // Show navigation arrows if there are more pages
    if (totalPages > 1) {
        if (page > 0) {
            display.setCursor(0, 56);
            display.print("< Prev");
        }
        if (page < totalPages - 1) {
            display.setCursor(60, 56);
            display.print("Next >");
        }
    }
    
    display.display();
}

// User-controlled text display with page navigation
void displayText(const char* text) {
    const int charWidth = 6;
    const int lineHeight = 8;
    const int charsPerLine = SCREEN_WIDTH / charWidth;
    const int maxLines = SCREEN_HEIGHT / lineHeight;
    
    // First, let's break the text into actual display lines
    // considering both newlines and word wrap
    String lines[50]; // Allow up to 50 lines
    int lineCount = 0;
    String currentLine = "";
    
    for (int i = 0; text[i] != '\0' && lineCount < 50; i++) {
        if (text[i] == '\n') {
            // Newline character - start new line
            if (currentLine.length() > 0) {
                lines[lineCount++] = currentLine;
            } else {
                lines[lineCount++] = " "; // Empty line
            }
            currentLine = "";
        } else {
            currentLine += text[i];
            // If current line exceeds screen width, wrap it
            if (currentLine.length() >= charsPerLine) {
                lines[lineCount++] = currentLine;
                currentLine = "";
            }
        }
    }
    
    // Add the last line if it's not empty
    if (currentLine.length() > 0 && lineCount < 50) {
        lines[lineCount++] = currentLine;
    }
    
    Serial.printf("Total lines: %d, Max lines per screen: %d\n", lineCount, maxLines);
    
    // If all lines fit on screen, display normally
    if (lineCount <= maxLines) {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        
        for (int i = 0; i < lineCount; i++) {
            display.println(lines[i]);
        }
        display.display();
        return;
    }
    
    // Text is too long - implement user-controlled page navigation
    int totalPages = (lineCount + maxLines - 1) / maxLines; // Ceiling division
    int currentPage = 0;
    
    Serial.println("\n=== TEXT NAVIGATION ===");
    Serial.println("Commands: n (next), p (previous), q (quit)");
    Serial.printf("Total pages: %d\n", totalPages);
    Serial.println("========================");
    
    bool quitNavigation = false;
    
    while (!quitNavigation) {
        // Display current page
        displayPage(lines, lineCount, maxLines, currentPage, totalPages);
        
        Serial.printf("Page %d/%d - [n]ext, [p]rev, [q]uit: ", currentPage + 1, totalPages);
        
        // Wait for user input with timeout
        unsigned long startTime = millis();
        bool gotInput = false;
        
        while (!gotInput && millis() - startTime < 10000) { // 10 second timeout
            if (Serial.available()) {
                char input = Serial.read();
                Serial.println(input); // Echo the input
                
                switch (input) {
                    case 'n': // Next page
                    case 'N':
                        if (currentPage < totalPages - 1) {
                            currentPage++;
                        } else {
                            Serial.println("Already on last page");
                        }
                        gotInput = true;
                        break;
                        
                    case 'p': // Previous page
                    case 'P':
                        if (currentPage > 0) {
                            currentPage--;
                        } else {
                            Serial.println("Already on first page");
                        }
                        gotInput = true;
                        break;
                        
                    case 'q': // Quit navigation
                    case 'Q':
                        quitNavigation = true;
                        gotInput = true;
                        Serial.println("Exiting navigation");
                        break;
                        
                    default:
                        Serial.println("Invalid command. Use n, p, or q");
                        break;
                }
            }
            delay(100);
        }
        
        // If timeout occurred without input, auto-advance to next page
        if (!gotInput && !quitNavigation) {
            Serial.println("Timeout - auto-advancing to next page");
            if (currentPage < totalPages - 1) {
                currentPage++;
            } else {
                currentPage = 0; // Wrap around to first page
            }
        }
    }
    
    // After navigation, show the first page again
    displayPage(lines, lineCount, maxLines, 0, totalPages);
    Serial.println("Navigation complete - showing first page");
}


// Universal display function
void universalDisplay(const char* text, int textSize, int xPos, int yPos, bool clearBefore, bool scroll, unsigned long scrollDelay, unsigned long displayDelay) {
    if (clearBefore) {
        display.clearDisplay();
    }
    
    display.setTextSize(textSize);
    display.setTextColor(WHITE);
    display.setCursor(xPos, yPos);
    display.print(text);
    display.display();
    
    if (displayDelay > 0) {
        delay(displayDelay);
    }
}

// Display static text without scrolling
void displayStaticText(const char* text, int textSize, int xPos, int yPos) {
    display.clearDisplay();
    display.setTextSize(textSize);
    display.setTextColor(WHITE);
    display.setCursor(xPos, yPos);
    display.print(text);
    display.display();
}

// Utility functions
int calculateTextWidth(const char* text, int textSize) {
    return strlen(text) * 6 * textSize;
}

int calculateTextLines(const char* text, int textSize) {
    int charWidth = 6 * textSize;
    int charsPerLine = SCREEN_WIDTH / charWidth;
    int textLength = strlen(text);
    return (textLength + charsPerLine - 1) / charsPerLine;
}

bool textNeedsScrolling(const char* text, int textSize) {
    int totalLines = calculateTextLines(text, textSize);
    int maxLines = SCREEN_HEIGHT / (8 * textSize);
    return totalLines > maxLines;
}

// Display the boot sequence
void displayBootSequence() {
    displayStaticText("System Operating", 1, 0, 0);
    delay(1000);
    
    displayStaticText("loading...", 1, 0, 16);
    delay(2000);
    
    display.clearDisplay();
    display.display();
}

// Display the "Welcome" message after boot
void displayWelcomeMessage() {
    displayStaticText("Welcome", 2, 20, 20);
    delay(2000);
}