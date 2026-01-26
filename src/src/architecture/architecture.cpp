#include "architecture.h"
#include "../core/output_handler.h" // output handled universally in the os through this
#include <Arduino.h>
#include <bits/stdc++.h>
#include <LittleFS.h>

// int consumes 8 bits , long long takes 16 bits
// i think i should use int to sustain for the constraints of esp
// total memory in a nodemcu is typically 4mb = 4 * 1024 * 1024 bits = 4194304 bits , so basically we can create 524288 integers in the memory
// lets me only allow 1/8th of that to be used as stack size , this is a stack based os yes
// instrction plan
// 1 = PUSH (put a number on the stack)
// 2 = LOAD (get a variable's value)
// 3 = STORE (save to a variable)
// 4 = ADD
// 5 = SUB
// 6 = MUL
// 7 = DIV
// 8 = PRINT
// 9 = HALT (stop)

int stack[64];
int top = 0; 

int variables[256];  // 256 slots for variables

int pc = 0;
std::vector<std::string> program(1024); // set of instructions form a program , did you know the size limit is 1024 lines , because esp is memory limited


void push(int value) {
    if (top < 64) {
        stack[top++] = value;
    }else{
        printOutput("Stack Overflow Error\n");
    }

}

int pop() {
    if (top > 0) {
        return stack[--top];
    }
    printOutput("Stack Underflow Error\n");
    return 0;
}

int peek() {
    if (top > 0) {
        return stack[top - 1];
    }
    printOutput("Stack is Empty\n");
    return 0;
}

void executor(std::string line){
    // todo
}

void loadProgram(const std::string& filename){
    // file will be read line by line using liitlefs to first get full file then cpp to read it line by line
    File file = LittleFS.open(filename.c_str(), "r");
    if (!file) {
        printOutput("Failed to open program file\n");
        return;
    }
    program.clear();
    pc = 0;
    String line;
    while (file.available()) {
        line = file.readStringUntil('\n');
        program.push_back(line.c_str());
        pc++;
        // instead of interpreting line by line we will first load the program into memory then run it as a whole
    }
    file.close();
    for (pc = 0; pc < program.size(); pc++){
        executor(program[pc]);
    }
}