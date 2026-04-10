this is currently a non-preemptive FCFS (First-Come, First-Served) based operating system.

it's non-preemptive because i haven't implemented a way to handle interrupts or context switching for user inputs while a program is running. for a more forceful "multitasking" nature i'd need buttons or threads, which i'm avoiding for now to keep things simple on the ESP8266.

## current state

the system runs on an ESP8266 with an OLED display. it boots up with a welcome sequence, initializes the filesystem, and drops you into a shell.

**WiFi Setup:** unlike before, WiFi setup doesn't happen automatically at boot (which was annoying). now you use the `wifi setup` command when you actually need it.

**Filesystem:** the project now has a functional filesystem based on LittleFS. you have a full set of unix-like commands: `ls`, `cd`, `pwd`, `mkdir`, `touch`, `rm`, `rmdir`, `cp`, and `mv`. there's even a simple file writer called `lexa` so you can create files directly from the shell.

**Configuration:** i've added "Tonic" (.tnc), a declarative configuration system. it lives at `/home/config.tnc` and stores things like your hostname, wifi credentials, and display settings in a clean, structured format.

**Extras:** the brainfuck interpreter is still there for the brave, and there's a weather/time utility that can pull data if you've got the credentials set up.

## architecture

restructured into **core**, **architecture**, and **extras**:

*   **core**: the backbone. handles the shell, output (serial + display), networking, and filesystem.
*   **architecture**: handles system-specific details and the Tonic configuration system.
*   **extras**: optional fun stuff like `bf` and `weather`. keeping them separate makes the core easier to maintain.

## planned roadmap

the big goal is still **Loom**, the package manager. i'm thinking of a custom language/bytecode format called **Elin** so we don't have to rely on brainfuck for user apps. the idea is to be able to fetch and run these packages from a remote repo.

display handling could also be improved. right now it paginates text because the screen is so small, but i want to make the display optional so you can do most work through a serial monitor if you prefer.

## limitations and quirks

memory is still tight. no multitasking means when a command is running, it owns the CPU. if you run a `bf` program that loops forever, you're gonna have to hit the reset button. the `ctrl_c` command is in the works but doesn't do much yet without proper process management.