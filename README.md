# system_operating

## Overview

`system_operating` is an experimental, minimal, shell-based operating system designed for microcontroller devices like the ESP8266. It provides a foundation for low-level runtime management, a comprehensive filesystem interface, declarative configuration, and basic external integrations (weather, brainfuck interpreter). The system focuses on constrained hardware, aiming to provide an efficient, lightweight environment for embedded experimentation.

---

## Current Progress

### Completed

*   **Core Boot Sequence**: Fully implemented in `src/system_operating.ino` and `src/src/core/init.cpp`.
*   **System Initialization**: Set up for Serial, Display, and LittleFS-based filesystem.
*   **Tonic Configuration System**: Implements a declarative configuration system using `.tnc` files (located at `/home/config.tnc`) for system, network, and display settings.
*   **Comprehensive Shell Interface**: Interactive REPL with support for system status, networking, and filesystem management.
*   **Filesystem Integration**: Full suite of filesystem utilities (`ls`, `pwd`, `cd`, `cat`, `mkdir`, `touch`, `rm`, `rmdir`, `cp`, `mv`, `lexa`).
*   **Output Handling**: Managed through a unified `output_handler` that supports both Serial and OLED display pagination.
*   **Modular Architecture**: Separated into **core** (essential OS modules), **architecture** (hardware-specific details and config), and **extras** (optional utilities).

### Under Development

*   **Loom Package Manager**: A planned package manager to handle installation and management of software packages.
*   **Elin Bytecode**: A custom language/bytecode format for user-made applications, intended to be managed by Loom.
*   **Multitasking**: Currently a non-preemptive FCFS system; future versions aim for improved process management.
*   **Enhanced Terminal**: Further improvements to the OLED-based display management and input handling.

---

## Project Structure

*   **`src/system_operating.ino`**: The main entry point and setup logic for the operating system.
*   **`src/src/core/`**: Core OS modules including initialization, shell interface, output management, networking, and filesystem.
*   **`src/src/architecture/`**: Architecture-specific helpers, system details, and the Tonic configuration implementation.
*   **`src/src/extras/`**: Additional utilities like the Brainfuck interpreter and weather/time features.
*   **`website/`**: Static site content for project documentation.

---

## Available Commands

| Command | Description |
| :--- | :--- |
| `help` | Shows the list of available commands. |
| `clear` | Clears the screen/output. |
| `stats` | Displays system information and memory status. |
| `wifi` | Shows current WiFi status. |
| `wifi setup` | Initiates the WiFi connection process. |
| `ls` | Lists files and directories in the current path. |
| `pwd` | Prints the current working directory. |
| `cd <path>` | Changes the current working directory. |
| `cat <file>` | Displays the contents of a file. |
| `mkdir <name>` | Creates a new directory. |
| `touch <file>` | Creates a new empty file. |
| `rm <file>` | Removes a specified file. |
| `rmdir <dir>` | Removes a specified directory. |
| `cp <src> <dst>` | Copies a file to a new location. |
| `mv <src> <dst>` | Moves or renames a file. |
| `lexa <file> <text>` | A simple file writer/editor to create or append content. |
| `weather` | Displays current weather information (requires credentials). |
| `bf` | Launches the Brainfuck code interpreter. |

---

## Tonic Configuration (.tnc)

The system uses a declarative configuration format called Tonic. The configuration file is stored at `/home/config.tnc`.

Example `config.tnc`:
```hcl
system {
    hostname = "system-operating";
    version = "1.0.0";
}

network {
    ssid = "YourSSID";
    password = "YourPassword";
}
```

---

## Future Goal: Loom & Elin

Loom is the planned package manager for `system_operating`, designed to handle the installation and update of software packages compiled into Elin bytecode.

### Key Concepts

*   **Package Management**: Registry-based approach to software distribution.
*   **Dependency Resolution**: Automatic tracking via `.tnc` configuration.
*   **Portability**: Elin bytecode will allow user applications to run across different builds of the OS.
