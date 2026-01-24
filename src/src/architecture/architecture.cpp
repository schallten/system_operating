#include "architecture.h"
#include "../core/output_handler.h" // output handled universally in the os through this
#include <Arduino.h>

// int consumes 8 bits , long long takes 16 bits
// i think i should use int to sustain for the constraints of esp
// total memory in a nodemcu is typically 4mb = 4 * 1024 * 1024 bits = 4194304 bits , so basically we can create 524288 integers in the memory
// lets me only allow 1/8th of that to be used as stack size , this is a stack based os yes

// variables
#define STACK_SIZE   1024     // 4 kb
#define MEMORY_SIZE  2048     // 8 kb
#define PROGRAM_SIZE 4096     // 4 kb

int stack[STACK_SIZE];      // stack memory
int memory[MEMORY_SIZE];    // general purpose memory
int program[PROGRAM_SIZE];  // program memory
int pc = 0;                 // program counter , stores current instruction
int sp = -1;                // stack pointer , aka top of stack



// functions to handle

void push(int value){
    if (sp>=STACK_SIZE){
        printOutput("Stack Overflow Error");
        return;
    }
    sp++;
    stack[sp] = value;
}

int pop(){
    if (sp<0){
        printOutput("Stack Underflow Error");
        return;
    }
    return stack[--sp];  
}

int peek(){
    if (sp<0){
        printOutput("Stack Underflow Error");
        return;
    }
    return stack[sp];
}

// for now , this is suffcient , after building VM for the langguage this can continue






