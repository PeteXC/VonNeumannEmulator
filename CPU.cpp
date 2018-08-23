#include <iostream>
#include <string.h>
#include <cstdio>
#include "CPU.h"

using namespace std;

void::CPU::IR_load() {

    strcpy(IR,MDR);
    IR[7] = '\0';
    PC++;

}

int::CPU::update_address_bus(int address) {
    return address;
}

char*::CPU::update_instructionbus(char *instruction) {
    return instruction;
}

void::CPU::IR_decode() {
    yesOP = true;
    strncpy(opcode,IR,3);                                                   /// Seperate IR into components
    opcode[3] = '\0';
    strncpy(operand1,IR + 3,5);
    operand1[2] = '\0';
    sscanf(operand1,"%d",&operand1_cast);

    if (!strcmp(opcode, "VAR")){
        yesOP = false;
    }
    else if (!strcmp(opcode, "NOP")){
        yesOP = false;
    }
    else if (!strcmp(opcode, "STO") || !strcmp(opcode, "JMP")){
        feedback = false;
    }
    else if (!strcmp(opcode, "MOV") || !strcmp(opcode, "CPY")){                                 /// Create a new component for operand 2
        feedback = true;
        strncpy(operand2,IR + 5,7);
        operand2[2] = '\0';
        sscanf(operand2,"%d",&operand2_cast);
    }
    else if (!strcmp(opcode, "HLT")){
        yesOP = false;
        Halt = true;
        cout << "HALTING" << endl;
    }
    else {
        feedback = true;
    }

    IR[5] = '\0';

}

void::CPU::MDR_decode() {
    MDR[7] = '\0';
    strncpy(MDR_opcode,MDR,3);
    MDR_opcode[3] = '\0';
    strncpy(MDR_operand1,MDR + 3,5);
    MDR_operand1[2] = '\0';
    sscanf(MDR_operand1,"%d",&MDR_operand1_cast);

}

void::CPU::CPU_execute(int data) {

    if (!strcmp(opcode, "LOD")){
        ALU_X = data;
        return;
    }
    else if (!strcmp(opcode, "ADD")){
        ALU_Y = data;
        Accumulator = ALU_X + ALU_Y;
        return;
    }
    else if (!strcmp(opcode, "ADX")){
        ALU_Y = data;
        Accumulator = Accumulator + ALU_Y;
        return;
    }
    else if (!strcmp(opcode, "SUB")){
        ALU_Y = data;
        Accumulator = ALU_X - ALU_Y;
        return;
    }
    else if (!strcmp(opcode, "SBX")){
        ALU_Y = data;
        Accumulator = Accumulator - ALU_Y;
        return;
    }
    else if (!strcmp(opcode, "DIV")){
        ALU_Y = data;
        Accumulator = ALU_X / ALU_Y;
        return;
    }
    else if (!strcmp(opcode, "DVX")){
        ALU_Y = data;
        Accumulator = Accumulator / ALU_Y;
        return;
    }
    else if (!strcmp(opcode, "MUL")){
        ALU_Y = data;
        Accumulator = ALU_X * ALU_Y;
        return;
    }
    else if (!strcmp(opcode, "MLX")){
        ALU_Y = data;
        Accumulator = Accumulator * ALU_Y;
        return;
    }
    else if (!strcmp(opcode, "MOD")){
        ALU_Y = data;
        Accumulator = ALU_X % ALU_Y;
        return;
    }
    else if (!strcmp(opcode, "MDX")){
        ALU_Y = data;
        Accumulator = Accumulator % ALU_Y;
        return;
    }


}

void::CPU::CPU_execute() {

    if (!strcmp(opcode, "STO")){
        int i = 0;                              // the array index
        char a[256];                            // the array

        while (Accumulator) {                   // loop till there's nothing left
            a[i++] = Accumulator % 10;          // assign the last digit
            Accumulator /= 10;                  // "right shift" the number     ///Reference: http://stackoverflow.com/questions/15987666/converting-integer-into-array-of-digits
        }

        strncpy(opcode,"VAR",3);                                ///     Save it as a variable
        operand1[1] = a[0] + '0';                               ///     Save the number into the operand array
        operand1[0] = a[1] + '0';
        strncpy(feedback_instruction,opcode,3);                 ///     Write the variable down as an instruction to be given back
        strncpy(feedback_instruction + 3,operand1,2);
        feedback_instruction[5] = '\0';
        return;
    }
    else if (!strcmp(opcode, "JMP")){
        if (jmp_cnt < 10) {
            PC = operand1_cast;
            jmp_cnt++;
        }
        else {
            cout << "Jump limit reached! Please check if program memory has infinite recursive jumping!" << endl;
            jmp_cnt = 0;
            Halt = true;
        }
        return;
    }
}

void::CPU::clearXY() {
    ALU_X, ALU_Y = 0;
}

char*::CPU::get_IR() {
    return IR;
}

int::CPU::get_PC() {
    return PC;
}

char*::CPU::get_opcode() {
    return opcode;
}

char*::CPU::get_feedback_instruction(){
    return feedback_instruction;
}

char*::CPU::get_operand1() {
    return operand1;
}
char*::CPU::get_operand2() {
    return operand2;
}

int::CPU::get_operand1_cast() {
    return operand1_cast;
}

int::CPU::get_operand2_cast() {
    return operand2_cast;
}


char*::CPU::get_MDR() {
    return MDR;
}

int::CPU::get_MAR() {
    return MAR;
}

char*::CPU::get_MDR_opcode() {
    return MDR_opcode;
}

int::CPU::get_MDR_operand() {
    return MDR_operand1_cast;
}

void::CPU::print_ALU() {
    cout << "ALUX:" << ALU_X << endl;
    cout << "ALUY:" << ALU_Y << endl;
    cout << "ACC:" << Accumulator << endl;
    return;
}

void::CPU::update(modes modes1, int address, char data[]) {
    mode = modes1;
    MAR = address;
    strcpy(MDR,data);
    MDR[7] = '\0';
}


void::CPU::CPU_RELOAD() {

    Halt = false;
    yesOP = true;
    PC = 0;
    ALU_X,ALU_Y,Accumulator = 0;

}

//
// Created by Peter Chai on 28/03/2017.
//
