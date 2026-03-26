// display.cpp
// this seriously needs a lot of understanding and cleanup and all that , which  i wont focus on right now as i will do all work with serial monitor
#include "display.h"
#include "config.h"
#include "output_handler.h"
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Initialize the display
void initializeDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        printlnOutput(F("SSD1306 allocation failed"));
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

// Console-like scrolling display buffer
#define MAX_CONSOLE_LINES 8
String consoleBuffer[MAX_CONSOLE_LINES];
int currentConsoleLine = 0;

void displayConsole(const char* text) {
    String input = String(text);
    int lastPos = 0;
    
    // If the buffer is empty, initialize the first line
    if (currentConsoleLine == 0 && MAX_CONSOLE_LINES > 0) {
        currentConsoleLine = 1;
        consoleBuffer[0] = "";
    }

    while (lastPos < input.length() || input.length() == 0) {
        int pos = input.indexOf('\n', lastPos);
        String linePart;
        bool hasNewline = (pos != -1);
        
        if (hasNewline) {
            linePart = input.substring(lastPos, pos);
            lastPos = pos + 1;
        } else {
            linePart = input.substring(lastPos);
            lastPos = input.length();
        }

        // Append the part to the current line
        consoleBuffer[currentConsoleLine - 1] += linePart;

        // If we hit a newline or the line is too long, move to next line
        if (hasNewline || consoleBuffer[currentConsoleLine - 1].length() >= 21) {
            if (currentConsoleLine < MAX_CONSOLE_LINES) {
                currentConsoleLine++;
                consoleBuffer[currentConsoleLine - 1] = "";
            } else {
                // Scroll up
                for (int i = 0; i < MAX_CONSOLE_LINES - 1; i++) {
                    consoleBuffer[i] = consoleBuffer[i + 1];
                }
                consoleBuffer[MAX_CONSOLE_LINES - 1] = "";
                // currentConsoleLine stays at MAX_CONSOLE_LINES
            }
        }
        
        if (input.length() == 0) break; // Handle empty string case
    }

    // Draw the buffer
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    // Draw all lines except the current one if it's empty and we have others
    int linesToDraw = currentConsoleLine;
    for (int i = 0; i < linesToDraw; i++) {
        display.setCursor(0, i * 8);
        display.print(consoleBuffer[i]);
    }
    display.display();
}

// User-controlled text display with page navigation
void displayPaginated(const char* text) {
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
    
    // If all lines fit on screen, display using console-like logic
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
    int totalPages = (lineCount + maxLines - 1) / maxLines; 
    int currentPage = 0;
    
    Serial.println("\n--- Paging Mode ---");
    Serial.println("Commands: n (next), p (previous), q (quit)");
    
    bool quitNavigation = false;
    while (!quitNavigation) {
        displayPage(lines, lineCount, maxLines, currentPage, totalPages);
        
        // Wait for user input with timeout
        unsigned long startTime = millis();
        bool gotInput = false;
        
        while (!gotInput && millis() - startTime < 10000) {
            if (Serial.available()) {
                char input = Serial.read();
                if (input == 'n' || input == 'N') {
                    if (currentPage < totalPages - 1) currentPage++;
                    gotInput = true;
                } else if (input == 'p' || input == 'P') {
                    if (currentPage > 0) currentPage--;
                    gotInput = true;
                } else if (input == 'q' || input == 'Q') {
                    quitNavigation = true;
                    gotInput = true;
                }
            }
            delay(10);
        }
        if (!gotInput) quitNavigation = true; // Timeout exits paging
    }
}

// Keep the old name for compatibility if needed, but route to console or paginated
void displayText(const char* text) {
    if (strlen(text) > 100) { // arbitrary threshold for paginated view
        displayPaginated(text);
    } else {
        displayConsole(text);
    }
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
    displayStaticText("HELOO THERE", 1, 0, 0);
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
