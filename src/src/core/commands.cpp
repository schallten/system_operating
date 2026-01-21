// commands.cpp
// Command execution implementation

#include "commands.h"
#include "config.h"
#include "network.h"
#include "display.h"
#include "monitor.h"
#include "filesystem.h"
#include "output_handler.h"
#include "../extras/timeundweather.h"
#include "../extras/bf.h"
#include <Arduino.h>

void executeCommand(const String &command) {
    // Parse command and arguments
    int spaceIndex = command.indexOf(' ');
    String cmd = (spaceIndex == -1) ? command : command.substring(0, spaceIndex);
    String args = (spaceIndex == -1) ? "" : command.substring(spaceIndex + 1);
    
    if (cmd == "help") {
        printlnOutput("Available commands: \n help: shows this message \n stats: shows system stats \n wifi: shows wifi status \n weather : display weather (needs credentials) \n bf: run brainfuck code \n ls: list files \n pwd: print working directory \n cd: change directory \n cat: display file contents \n mkdir: make folder \n touch: create file \n rm: remove file \n rmdir: remove folder \n cp: copy file \n mv: move/rename file \n lexa: edit/write to file");
        
    } else if (cmd == "stats") {
        printlnOutput(getSystemStats().c_str());
    } else if (cmd == "wifi") {
        printlnOutput(getWiFiStatus().c_str());
    } else if (cmd == "weather") {
        getWeathDetails();
    } else if (cmd == "bf") {
        runBFProgram();
    } else if (cmd == "ctrl_c") {
        printlnOutput("No program is currently running.");
        delay(2000);
        printlnOutput("This feature is under works");
        printlnOutput("This feature is under works, when in future versions proper multitasking is employed you will be able to stop running programs");
    } 
    // Filesystem commands
    else if (cmd == "ls") {
        list();
    } else if (cmd == "pwd") {
        printWorkingDirectory();
    } else if (cmd == "cd") {
        if (args.isEmpty()) {
            printlnOutput("Error: no directory specified");
        } else {
            changeDirectory(args.c_str());
        }
    } else if (cmd == "cat") {
        if (args.isEmpty()) {
            printlnOutput("Error: no file specified");
        } else {
            cat(args.c_str());
        }
    } else if (cmd == "mkdir") {
        if (args.isEmpty()) {
            printlnOutput("Error: no folder name specified");
        } else {
            makeFolder(args.c_str());
        }
    } else if (cmd == "touch") {
        if (args.isEmpty()) {
            printlnOutput("Error: no file name specified");
        } else {
            createFile(args.c_str());
        }
    } else if (cmd == "rm") {
        if (args.isEmpty()) {
            printlnOutput("Error: no file specified");
        } else {
            removeFile(args.c_str());
        }
    } else if (cmd == "rmdir") {
        if (args.isEmpty()) {
            printlnOutput("Error: no folder specified");
        } else {
            removeFolder(args.c_str());
        }
    } else if (cmd == "cp") {
        int spaceInArgs = args.indexOf(' ');
        if (spaceInArgs == -1) {
            printlnOutput("Error: cp requires source and destination");
        } else {
            String source = args.substring(0, spaceInArgs);
            String destination = args.substring(spaceInArgs + 1);
            copyFile(source.c_str(), destination.c_str());
        }
    } else if (cmd == "mv") {
        int spaceInArgs = args.indexOf(' ');
        if (spaceInArgs == -1) {
            printlnOutput("Error: mv requires source and destination");
        } else {
            String source = args.substring(0, spaceInArgs);
            String destination = args.substring(spaceInArgs + 1);
            moveFile(source.c_str(), destination.c_str());
        }
    } else if (cmd == "lexa") {
        int spaceInArgs = args.indexOf(' ');
        if (spaceInArgs == -1) {
            printlnOutput("Error: lexa requires filename and content");
        } else {
            String filename = args.substring(0, spaceInArgs);
            String content = args.substring(spaceInArgs + 1);
            lexa(filename.c_str(), content.c_str());
        }
    } else {
        printlnOutput("Unknown command. Type 'help' for a list of commands.");
    }
}
