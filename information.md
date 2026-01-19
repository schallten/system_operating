this is "currently" a non-preemptive FCFS based operating system.

non preemptive due to the reason due to unable to take inputs in a way that i can't understand for now. for forceful nature i would need to use buttons or use threads , which i am deciding to avoid for now.

## current state

the system runs on an ESP8266 with an OLED display. it boots up, shows a welcome screen, handles wifi setup, and provides a basic shell interface. you can run commands like `stats` to check system memory, `wifi` to see network status, and even run a brainfuck interpreter if you're into that sort of thing. the display is paginated so you can scroll through longer text outputs.

## planned roadmap

for now after completing "fs" using littlefs or any such module the project will switch to a shell first approach , providing a shell to run many functions , in the same fashion as before ofc , maybe a timeout after last line has been written before which it returns to the shell back again

the big goal after that is a package manager , for which it is planned to have a custom language as relying on brainf*ck for custom user made apps doesn't seem to be a viable solution. thinking something simple that can be compiled on the device or fetched from somewhere. still figuring out the details tho

display will also be made optional so that most of the work can be done using the arduino ide's system monitor , the graphics can be handled later by making a device manager to extend this os to a fully functional , of its scale , computer

## architecture

recently restructured everything into **core** and **extras** modules to keep things clean:

**core** contains the essential stuff - initialization, display, networking, shell, and command handling. these are the backbone operations that always run

**extras** are the optional features like weather pulling and the brainfuck interpreter. they can be added or removed without breaking the core system

keeps things modular and makes it easier to add new features without cluttering the main codebase

## limitations and quirks

memory is tight on the ESP8266 so we're pretty limited. can't do fancy multitasking or heavy lifting. the OLED display is small so text wraps and paginates. the whole thing runs single-threaded which means one thing at a time, no interrupts handling user input while stuff is running

also the wifi setup happens at boot right now, which is kinda annoying. eventually should be able to skip it or reconfigure on the fly
 