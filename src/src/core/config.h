// config.h
// Centralized configuration and constants for the system

#ifndef CONFIG_H
#define CONFIG_H

// OLED Display Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
#define CHAR_WIDTH 6
#define LINE_HEIGHT 8
#define CHARS_PER_LINE (SCREEN_WIDTH / CHAR_WIDTH)
#define MAX_LINES (SCREEN_HEIGHT / LINE_HEIGHT)

// Serial Configuration
#define SERIAL_BAUD 9600

// Network Configuration
#define CONNECTION_TIMEOUT 5000
#define MAX_RETRIES 3
#define PING_SERVER_HOST "8.8.8.8"

// Timing Configuration (in milliseconds)
#define BOOT_DISPLAY_DELAY 3000
#define SETUP_COMPLETE_DELAY 3000
#define SERIAL_WAIT_DELAY 100

// Shell Command Flags
#define EXIT_DISPLAY_FLAG 'q'
#define NEXT_PAGE_FLAG 'n'
#define PREV_PAGE_FLAG 'p'

// Weather API Configuration
#define WEATHER_API_URL "http://api.open-meteo.com/v1/forecast"

#endif
