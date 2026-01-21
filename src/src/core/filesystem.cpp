// functions for fs via littlefs
#include <Arduino.h>
#include <LittleFS.h>
#include "filesystem.h"
#include "output_handler.h"

// variables
bool firstBoot = false;
String current_dir = "/";

bool createEssentials(bool firstBoot){
    if (firstBoot){
        LittleFS.mkdir("/home");
        LittleFS.mkdir("/home/config"); // user stored configs here , OS doesn;t support multi users
        LittleFS.mkdir("/history"); // history of commands run is stored in a file in this folder
        LittleFS.mkdir("/apps"); // all bins and installed apps stored here
        LittleFS.mkdir("/tmp"); // temporary files stored here
        // create history file
        File historyFile = LittleFS.open("/history/commands.txt", "w");
        if (historyFile) {
            historyFile.println("// Command History File");
            historyFile.close();
        }
        return true;
    }
    else {
        return false;
    }// really usless tbh
}

bool initFilesystem() {
    if (!LittleFS.begin()) {
        printlnOutput("An error has occurred while mounting LittleFS");
        return false;
    } else {
        printlnOutput("LittleFS mounted successfully");
        return true;
    }
}

void initalizeSystem(){
    // first we will create the donotdelete.txt while will contain : 1 for true ( means os is not booting for the first time ) and 0 for false ( means os is booting for the first time )
    File configFile = LittleFS.open("/donotdelete.txt", "r");
    if (!configFile) {
        // file does not exist, so this is first boot
        firstBoot = true;
        // create the file and write 1 to it
        File newConfigFile = LittleFS.open("/donotdelete.txt", "w");
        if (newConfigFile) {
            newConfigFile.println("1");
            newConfigFile.close();
        }
        createEssentials(firstBoot);
    } else {
        // file exists, so this is not first boot
        firstBoot = false;
    }
}

void list(){
    File root = LittleFS.open(current_dir, "r");
    File file = root.openNextFile();
    while (file) {
        printOutput(file.name());
        if (file.isDirectory()) {
            printlnOutput(" <DIR>");
        } else {
            printOutput(" \t");
            printlnOutput(String(file.size()));
        }
        file = root.openNextFile();
    }
}

void cat(const char* filename){
    String filepath = current_dir + "/" + String(filename);
    File file = LittleFS.open(filepath, "r");
    if (!file){
        printlnOutput("Error opening file for reading");
        return;
    }
    while (file.available()){
        printCharOutput(file.read());
    }
    file.close();
}

void removeFile(const char* filename){
    String filepath = current_dir + "/" + String(filename);
    if (LittleFS.remove(filepath)){
        printlnOutput("File removed successfully");
    } else {
        printlnOutput("Error removing file");
    }
}

void removeFolder(const char* foldername){
    String folderpath = current_dir + "/" + String(foldername);
    if (LittleFS.rmdir(folderpath)){
        printlnOutput("Folder removed successfully");
    } else {
        printlnOutput("Error removing folder");
    }
}

void makeFolder(const char* foldername){
    String path = current_dir + "/" + String(foldername);
    if (LittleFS.mkdir(path)){
        printlnOutput("Folder created successfully");
    } else {
        printlnOutput("Error creating folder");
    }
}

void changeDirectory(const char* path){
    String newPath = String(path);
    if (!newPath.startsWith("/")) { // if user gives path like "home" instead of "/home"
        newPath = current_dir + "/" + newPath;
    }
    File dir = LittleFS.open(newPath, "r");
    if (dir && dir.isDirectory()){
        current_dir = newPath;
        printlnOutput("Directory changed to " + current_dir);
    } else {
        printlnOutput("Directory does not exist");
    }
}

void createFile(const char* filename){
    String filepath = current_dir + "/" + String(filename);
    File file = LittleFS.open(filepath,"w");
    if (file){
        printlnOutput("File created successfully");
        file.close();
    } else {
        printlnOutput("Error creating file");
    }
}

void lexa(const char* filename, const char* content){
    String filepath = current_dir + "/" + String(filename);
    File file = LittleFS.open(filepath, "w");
    if (file){
        file.print(String(content));
        printlnOutput("File written successfully");
        file.close();
    } else {
        printlnOutput("Error opening file for writing");
    }
}

// next up sometime instead of content being passed like this , it will be a text editor

void copyFile(const char* source,const char* destination){
    String srcPath = current_dir + "/" + String(source);
    String destPath = current_dir + "/" + String(destination);
    File srcFile = LittleFS.open(srcPath, "r");
    if (!srcFile){
        printlnOutput("Source file does not exist");
        return;
    }
    File destFile = LittleFS.open(destPath, "w");
    if (!destFile){
        printlnOutput("Error creating destination file");
        srcFile.close();
        return;
    }
    while (srcFile.available()){
        destFile.write(srcFile.read());
    }
    printlnOutput("File copied successfully");
    srcFile.close();
    destFile.close();
}

void moveFile(const char* source, const char* destination){
    String srcPath = current_dir + "/" + String(source);
    String destPath = current_dir + "/" + String(destination);
    if (LittleFS.rename(srcPath, destPath)){
        printlnOutput("File moved/renamed successfully");
    } else {
        printlnOutput("Error moving/renaming file");
    }
}

void printWorkingDirectory(){
    printlnOutput("Current Directory: " + current_dir);
}


// its so easy i almost feel like i am doing something wrong , well whatever