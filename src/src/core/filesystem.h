#ifndef FILESYSTEM_H
#define FILESYSTEM_H


void initalizeSystem(); // ran on only first run of the os to create all needed files and folders needed for os
bool initFilesystem(); // initializes the filesystem
bool createEssentials(bool firstBoot);
void list(); // lits files in current directory // like ls command in linux tbh
void cat(const char* filename); // prints file contents to serial monitor
void removeFile(const char* filename); // removes a file
void removeFolder(const char* foldername); // removes a folder
void makeFolder(const char* foldername); // makes a folder
void changeDirectory(const char* path); // changes current directory
void createFile(const char* filename); // creates a new empty file
void lexa(const char* filename,const char* content); // like nano but differently named for this os
void copyFile(const char* source, const char* destination); // copies a file
void moveFile(const char* source, const char* destination); // moves a file or rename it
void printWorkingDirectory(); // prints the current directory path



#endif