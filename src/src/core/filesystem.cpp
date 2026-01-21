// functions for fs via littlefs
#include <Arduino.h>
#include <LittleFS.h>
#include "filesystem.h"

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
        Serial.println("An error has occurred while mounting LittleFS");
        return false;
    } else {
        Serial.println("LittleFS mounted successfully");
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
        Serial.print(file.name());
        if (file.isDirectory()) {
            Serial.println(" <DIR>");
        } else {
            Serial.print(" \t");
            Serial.println(file.size(), DEC);
        }
        file = root.openNextFile();
    }
}

void cat(const char* filename){
    String filepath = current_dir + "/" + String(filename);
    File file = LittleFS.open(filepath, "r");
    if (!file){
        Serial.println("Error opening file for reading");
        return;
    }
    while (file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void removeFile(const char* filename){
    String filepath = current_dir + "/" + String(filename);
    if (LittleFS.remove(filepath)){
        Serial.println("File removed successfully");
    } else {
        Serial.println("Error removing file");
    }
}

void removeFolder(const char* foldername){
    String folderpath = current_dir + "/" + String(foldername);
    if (LittleFS.rmdir(folderpath)){
        Serial.println("Folder removed successfully");
    } else {
        Serial.println("Error removing folder");
    }
}

void makeFolder(const char* foldername){
    String path = current_dir + "/" + String(foldername);
    if (LittleFS.mkdir(path)){
        Serial.println("Folder created successfully");
    } else {
        Serial.println("Error creating folder");
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
        Serial.println("Directory changed to " + current_dir);
    } else {
        Serial.println("Directory does not exist");
    }
}

void createFile(const char* filename){
    String filepath = current_dir + "/" + String(filename);
    File file = LittleFS.open(filepath,"w");
    if (file){
        Serial.println("File created successfully");
        file.close();
    } else {
        Serial.println("Error creating file");
    }
}

void lexa(const char* filename, const char* content){
    String filepath = current_dir + "/" + String(filename);
    File file = LittleFS.open(filepath, "w");
    if (file){
        file.print(String(content));
        Serial.println("File written successfully");
        file.close();
    } else {
        Serial.println("Error opening file for writing");
    }
}

// next up sometime instead of content being passed like this , it will be a text editor

void copyFile(const char* source,const char* destination){
    String srcPath = current_dir + "/" + String(source);
    String destPath = current_dir + "/" + String(destination);
    File srcFile = LittleFS.open(srcPath, "r");
    if (!srcFile){
        Serial.println("Source file does not exist");
        return;
    }
    File destFile = LittleFS.open(destPath, "w");
    if (!destFile){
        Serial.println("Error creating destination file");
        srcFile.close();
        return;
    }
    while (srcFile.available()){
        destFile.write(srcFile.read());
    }
    Serial.println("File copied successfully");
    srcFile.close();
    destFile.close();
}

void moveFile(const char* source, const char* destination){
    String srcPath = current_dir + "/" + String(source);
    String destPath = current_dir + "/" + String(destination);
    if (LittleFS.rename(srcPath, destPath)){
        Serial.println("File moved/renamed successfully");
    } else {
        Serial.println("Error moving/renaming file");
    }
}

void printWorkingDirectory(){
    Serial.println("Current Directory: " + current_dir);
}


// its so easy i almost feel like i am doing something wrong , well whatever