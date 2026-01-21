// bf.cpp
#include "bf.h"
#include "../core/display.h"
#include "../core/output_handler.h"

#include <Arduino.h>
#include <FS.h> 
#include <ESP8266WiFi.h>
#include <SPI.h>

#define TAPE_SIZE 30000 // this is size of memory tape , aka number of cells

uint8_t tape[TAPE_SIZE]; // array that represents the memory tape
uint8_t* pointer = tape; // pointer to current memory cell on the tape

String final; // to store the final output , to which values are added when needed and final is displayed after program ends

// brainf*ck interpretor function
void interpret(const char* program){
    int program_counter = 0; //  points to current position in the pgoram (brainfuck code)
    int program_length = strlen(program);

    // set all memory cells to zero
    memset(tape, 0 , TAPE_SIZE);

    // loop through each command in the input program
    while (program_counter<program_length){
        char cmd = program[program_counter];
        
        switch(cmd){
            case '>': // move pointer to the right (next memory cell)
                if (pointer<tape+TAPE_SIZE-1) pointer++;// prevent pointer overflow
                break;
            case '<': // move pointer to the left ( previous memory  cell )
                if (pointer>tape) pointer--; // prevent pointer underflow
                break;
            case '+': // increae value of current cell by 1
                (*pointer)++;
                break;
            case '-':
                (*pointer)--;
                break;
            case '.': // output the character at current memory cell
                printCharOutput(*pointer);
                final+=char(*pointer); // adding to the final string
                break;
            case ',': // input a character and store it in current memory cell
                while (Serial.available()==0); // wait for input
                printlnOutput("Please enter a character:");
                printlnOutput("Please input data in serial monitor");
                *pointer = Serial.read();
                break;
            case '[': // if current cell value is zero , jump to command after the matching closing bracket that is ']'
                // in simple words this is the start of a loop and if the current cell is zero , we skip the loop
                // cuurent pointer is the pointer we are reading right now
                // it being zero means there were no instructions passed to it that might have changed its values
                // hence we move forward
                if (*pointer==0){
                    int open_brackets = 1; // count the number of open brackets
                    while (open_brackets!=0){
                        program_counter++; // we move to the next charactere because we are looking for the matching closing bracket
                        if (program[program_counter]=='[') open_brackets++; // if we find another opening bracket , we increase the count
                        else if (program[program_counter]==']') open_brackets--; // if we find a closing bracket , we decrease the count
                    }
                }
                break;

            case ']':  // Jump backward to the corresponding '[' if the current memory cell is non-zero
                if (*pointer != 0) {
                    int close_brackets = 1;  // To keep track of bracket pairs
                    while (close_brackets != 0) {
                        program_counter--;  // Move back to the previous character
                        if (program[program_counter] == ']') close_brackets++;  // Found another closing bracket
                        if (program[program_counter] == '[') close_brackets--;  // Found an opening bracket
                    }
                }
                break;
        }

        program_counter++; // move to the next command in the program
    }
}

void runBFProgram(){
    String code;
    printlnOutput("Please enter your brainfuck code in the serial monitor");
    printlnOutput("Please enter your brainfuck code below : ");
    while (code.length()==0){
        if (Serial.available()>0){
            code = Serial.readStringUntil('\n'); // read the input until newline character  
            code.trim(); // remove any leading or trailing whitespace
        }
    }
    printlnOutput("Running your brainfuck code...");
    printlnOutput("Running your brainfuck code .. ");
    interpret(code.c_str()); // pass code to interpretor
    printlnOutput("\nProgram finished executing.");
    printlnOutput("Final Output: " + final);
    String realfinal = "bf output :\n" + final;
    printlnOutput(realfinal.c_str());
    final=""; // reset final for next run
    printlnOutput("Your output is " + realfinal);
}
