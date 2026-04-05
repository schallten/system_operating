# system_operating

## Overview

`system_operating` is an experimental, minimal operating system designed for microcontroller devices. It provides a foundation for low-level runtime management, a simple shell interface, package management, and repository-backed application deployment. The system focuses on constrained hardware, with the goal of providing an efficient, lightweight environment.

---

## Current Progress

### Completed

* **Core Boot Sequence**: Implemented in `src/system_operating.ino`.
* **System Initialization**: Set up in `src/core/init.h` and `src/core/init.cpp`.
* **Shell Integration**: Basic shell entry point in `src/core/shell.h` and `src/core/shell.cpp`.
* **Output Handling**: Managed in `src/core/output_handler.h` and `src/core/output_handler.cpp`.
* **Configuration Constants**: Defined in `src/core/config.h`.
* **Initial Help Command & Startup Messaging**: Basic functionality for user guidance.

### Under Development

* **Shell Command Parsing**: Building interactive REPL behavior for system control.
* **Filesystem Support**: Enabling persistent state management and handling of package metadata.
* **Network Functionality**: Developing functionality for repository access and downloading packages.
* **Package Manager**: Loom is being integrated as the system's package manager, handling software deployment and updates.
* **Validation & Verification**: Adding checksum verification and safe install workflows to ensure system integrity.

---

## Project Structure

* **`src/system_operating.ino`**: The main entry point and setup logic for the operating system.
* **`src/core/`**: Core OS modules including initialization, shell interface, output management, networking, and filesystem.
* **`src/architecture/`**: Architecture-specific helpers and details.
* **`src/extras/`**: Additional utilities and features that extend system capabilities.
* **`website/`**: Static site content for project documentation and user access.

---

## Loom: The Elin Package Manager for system_operating

Loom is the built-in package manager for `system_operating`, designed to handle the installation, management, and update of software packages compiled into Elin bytecode. Loom is deeply integrated into the system, offering the following features:

### Key Features

* **Package Management**: Loom manages Elin bytecode packages, providing a registry-based approach to software distribution.
* **Dependency Resolution**: Automatically tracks and resolves dependencies through `.tnc` configuration files, ensuring a smooth installation experience.
* **Package Installation**: Loom fetches, installs, and updates packages directly from the repository, ensuring the system remains up to date with minimal user intervention.
* **Backup & Recovery**: Loom provides built-in backup functionality, automatically backing up the home folder before updates to prevent data loss. This makes recovery straightforward, ensuring that even in the event of a failed update, the system can be restored safely.

### Workflow

1. **Write Code**: Develop and compile code locally in Elin bytecode format.
2. **Upload Packages**: Upload your compiled packages to the Loom repository portal.
3. **Install & Manage Packages**: Use Loom to install and manage packages on the device, tracking dependencies and ensuring system consistency.
4. **Backup & Recovery**: Loom automatically backs up critical system files before any update to prevent accidental data loss. You can easily recover to a previous state if needed.
