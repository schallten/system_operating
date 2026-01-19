# **System Operating**

### A learning project to build a pseudo-operating system for microcontrollers (ESP8266, ESP32, and others).

This document serves as a guide for me and any future contributors to track progress and share ideas.

---

## **The Plan**

###### *This plan will evolve as development progresses.*

---

### **Stage 1: Getting Started**

The first stage focuses on setting up basic system information and network connectivity. Here’s the breakdown of the features I’m working on:

*(Currently developing on an ESP8266 NodeMCU with an OLED display.)*

---

### **Completed Tasks**

* [x] **Boot Sequence**: Created a simple animation or text to display the system name and a "loading" message.

* [x] **Welcome Message**: Displayed a basic welcome message on the screen after boot.

* [x] **Fetch System Stats**: Retrieved system information such as available memory and free space, then displayed it on the OLED screen.

* [x] **Network Initialization**: Took **SSID** and **password** input from the serial monitor and used them to connect to Wi-Fi.

* [x] **Network Status Check**: After Wi-Fi connection, the system pings a server (like `google.com`) to verify network status.

* [x] **Initial Setup Complete**: Displayed the message "Initial setup complete" once everything was properly set up and functional.

---

### **Conclusion**

Stage 1 is now complete! All core features for system startup and network connectivity are functional.

---

### **Stage 2: Expanding Features**

In Stage 2, we focus on adding more interactive and functional features to the system. Here's the breakdown:

* [x] **Clock and Weather**

  * Fetch time and weather information using online sources (no external RTC modules).
  * Display the current time and weather (temperature, conditions, etc.) on the OLED screen.

* [x] **Brainfuck Compiler**

  * Develop a simple Brainfuck interpreter to run Brainfuck code on the system.
  * Display the results of executed code via the serial monitor or the OLED display.

* [x] **Basic Shell with Custom Syntax**

  * Implement a basic command-line interface (CLI) with custom commands.
  * Write `help` to see all commands.
  * Allow for future expansion of more commands and custom syntax.

---

### **Stage 3: Advanced System Functionality**

In Stage 3, the focus shifts to enhancing system functionality with advanced features like file system support and file manipulation commands.

#### **1. File System Support**

Implement a basic file system to allow for saving and loading of files. Since you're using a microcontroller, you might want to start with something lightweight like SPIFFS (Serial Peripheral Interface Flash File System) or LittleFS.

**Tasks:**

* [ ] Create commands like `ls`, `cat`, `rm`, `touch`, `cp`, etc., for interacting with files.

* [ ] Implement a basic text file editor (maybe through serial monitor input) to create and edit files.

* [ ] Allow users to write data to a file and read it back.

* [ ] Use LittleFS for better wear management ( may change ).

---

### **Stage 4: Shell Refinement**

After filesystem is solid, refine the shell core with better command handling and system services.

**Phase 1 — Shell Core Foundation**

* [ ] Command parser (input → tokens)
* [ ] Command registry (name, help, handler)
* [ ] `help` auto-generated from registry
* [ ] Return codes (`OK`, `ERR`, `INVALID`)
* [ ] Serial = input, OLED = output only

**Core Commands**

* [ ] `help` — show all available commands
* [ ] `clear` — clear display
* [ ] `reboot` — restart system
* [ ] `sysinfo` — system information
* [ ] `uptime` — system uptime

**Phase 2 — System Services**

Networking Service
* [ ] Wi-Fi service abstraction
* [ ] `net status` — show connection status
* [ ] `net connect` — connect to SSID
* [ ] `net ping` — ping a host

Time Service
* [ ] NTP sync from internet
* [ ] Timezone offset support
* [ ] `time now` — display current time
* [ ] `time sync` — sync with NTP

**Phase 3 — Applications as Modules**

* [ ] App interface standardization (init, run, exit)
* [ ] Brainfuck interpreter as modular app
  * [ ] `bf run file.bf`
* [ ] Weather app as modular feature
  * [ ] `weather now`
  * [ ] Cache results

---

### **Stage 5: Custom Language & VM**

Develop a lightweight custom language and virtual machine for user applications.

**Phase 0 — Design the Spec**

* [ ] Choose VM model → Stack-based
* [ ] Fix VM limits (stack size, memory cells, program size)
* [ ] Define syscall interface (print, read, time, fs, exit)
* [ ] No dynamic allocation, no recursion

**Phase 1 — Bytecode & VM Core**

Instruction Set
* [ ] PUSH const
* [ ] POP
* [ ] ADD / SUB / MUL / DIV
* [ ] LOAD addr / STORE addr
* [ ] JMP addr / JZ addr (conditional jump)
* [ ] SYSCALL id
* [ ] HALT

VM Implementation
* [ ] Stack (static array)
* [ ] Memory array
* [ ] Instruction pointer
* [ ] Bounds checking (crash safely)
* [ ] Bytecode format (header + flat instruction stream)
* [ ] Interpreter loop with opcode switch

**Phase 2 — Syscalls & OS Integration**

* [ ] `SYS_PRINT` → shell output
* [ ] `SYS_READ` → shell input
* [ ] `SYS_TIME` → current time
* [ ] `SYS_FS_READ` → read from filesystem
* [ ] `SYS_FS_WRITE` → write to filesystem
* [ ] `SYS_EXIT` → exit with code

**Phase 3 — Language Compiler (PC side)**

Minimal language with:
* [ ] Variables (`let x = 5`)
* [ ] Arithmetic expressions
* [ ] If / while control flow
* [ ] Print statements
* [ ] Exit codes

---

### **Conclusion**

Stage 1 is complete! Stages 2-5 are the roadmap for expanding this into a functional mini-OS.
