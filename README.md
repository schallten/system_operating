# System Operating

### A learning project to build a pseudo-operating system for microcontrollers (ESP8266, ESP32, and others).

#### This document serves as a guide for me and any future contributors to track progress and share ideas.

---

## The Plan

###### *This plan will evolve as development progresses.*

---

### Stage 1: Getting Started

The first stage focuses on setting up basic system information and network connectivity. Here’s the breakdown of the features I’m working on:

*(Currently developing on an ESP8266 NodeMCU with an OLED display.)*

---

### Completed Tasks

- [x] **Boot Sequence**  
  Created a simple animation or text to display the system name and a "loading" message.

- [x] **Welcome Message**  
  Displayed a basic welcome message on the screen after boot.

- [x] **Fetch System Stats**  
  Retrieved system information such as available memory and free space, then displayed it on the OLED screen.

- [x] **Network Initialization**  
  Took **SSID** and **password** input from the serial monitor and used them to connect to Wi-Fi.

- [x] **Network Status Check**  
  After Wi-Fi connection, the system pings a server (like `google.com`) to verify network status.

- [x] **Initial Setup Complete**  
  Displayed the message "Initial setup complete" once everything was properly set up and functional.

---

### Conclusion

Stage 1 is now complete! All core features for system startup and network connectivity are functional.

---

### Stage 2: Expanding Features

In Stage 2, we focus on adding more interactive and functional features to the system. Here's the breakdown:

- [ ] **Clock and Weather**  
  - Fetch time and weather information using online sources (no external RTC modules).
  - Display the current time and weather (temperature, conditions, etc.) on the OLED screen.

- [ ] **Brainfuck Compiler**  
  - Develop a simple Brainfuck interpreter to run Brainfuck code on the system.
  - Display the results of executed code via the serial monitor or the OLED display.

- [ ] **Basic Shell with Custom Syntax**  
  - Implement a basic command-line interface (CLI) with custom commands.
  - Example commands:
    - `time` - Display the current time.
    - `weather` - Fetch and display the latest weather data.
    - `status` - Show system stats (e.g., memory, Wi-Fi status).
    - `reboot` - Reboot the system.
    - `shutdown` - Shutdown or reset the system.
  - Allow for future expansion of more commands and custom syntax.

---


