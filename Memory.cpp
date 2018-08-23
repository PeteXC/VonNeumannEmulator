#include <iostream>
#include <string.h>
#include "Memory.h"

using namespace std;


Memory::Memory(examples example) {

    for(int p = 0; p < get_size(); p++){
        strcpy(memory_cells[p],"NOP##");                                        ///     clear out all the memory cells to NOP##
    }

    switch (example){

        case ADD:
            strcpy(memory_cells[0],"NOP##");                   ///    this is an empty cell with no opcode or operand
            strcpy(memory_cells[1],"LOD13");                   ///    this cell tells to load from 13
            strcpy(memory_cells[2],"ADD14");                   ///    this cell tells to add from 14
            strcpy(memory_cells[3],"STO16");                   ///    this cell tells to store in 15
            strcpy(memory_cells[4],"LOD13");
            strcpy(memory_cells[5],"ADD14");
            strcpy(memory_cells[6],"ADX15");                   ///    this cell tells to add data in address 15 to the accumulator
            strcpy(memory_cells[7],"STO17");
            strcpy(memory_cells[9],"HLT##");
            strcpy(memory_cells[13],"VAR07");
            strcpy(memory_cells[14],"VAR06");
            strcpy(memory_cells[15],"VAR07");
            break;

        case SUB:
            strcpy(memory_cells[0],"NOP##");                   ///    this is an empty cell with no opcode or operand
            strcpy(memory_cells[1],"LOD13");                   ///    this cell tells to load from 13
            strcpy(memory_cells[2],"SUB14");                   ///    this cell tells to subtract data in 14 from ALUX
            strcpy(memory_cells[3],"STO16");                   ///    this cell tells to store in 15
            strcpy(memory_cells[4],"LOD13");                   ///    this cell tells to add data in address 13 to the accumulator
            strcpy(memory_cells[5],"SUB14");
            strcpy(memory_cells[6],"SBX15");                   ///    this cell tells to subtract data in address 15 to the accumulator
            strcpy(memory_cells[7],"STO17");
            strcpy(memory_cells[9],"HLT##");
            strcpy(memory_cells[13],"VAR34");
            strcpy(memory_cells[14],"VAR04");
            strcpy(memory_cells[15],"VAR07");
            break;

        case JMP:
            strcpy(memory_cells[0],"JMP12");                   ///    this is an empty cell with no opcode or operand
            strcpy(memory_cells[1],"LOD07");                   ///    this cell tells to load from 7
            strcpy(memory_cells[2],"DIV08");                   ///    this cell tells to divide from 8
            strcpy(memory_cells[3],"STO10");                   ///    this cell tells to store in 10
            strcpy(memory_cells[5],"HLT##");
            strcpy(memory_cells[6],"VAR03");                   ///    this cell saves a variable "3", and cannot be changed, only moved or overwritten
            strcpy(memory_cells[7],"VAR12");
            strcpy(memory_cells[8],"VAR02");
            strcpy(memory_cells[12],"HLT##");

            break;

        case MOD:
            strcpy(memory_cells[0],"NOP##");                   ///    this is an empty cell with no opcode or operand
            strcpy(memory_cells[1],"LOD13");                   ///    this cell tells to load from 13
            strcpy(memory_cells[2],"MOD14");                   ///    this cell tells to modulo operate data in 14 from ALUX
            strcpy(memory_cells[3],"STO16");                   ///    this cell tells to store in 16
            strcpy(memory_cells[4],"LOD13");                   ///    this cell tells to add data in address 13 to the accumulator
            strcpy(memory_cells[5],"SUB12");
            strcpy(memory_cells[6],"MDX15");                   ///    this cell tells to modulo operate data in address 15 to the accumulator
            strcpy(memory_cells[7],"STO17");
            strcpy(memory_cells[9],"HLT##");
            strcpy(memory_cells[12],"VAR07");
            strcpy(memory_cells[13],"VAR34");
            strcpy(memory_cells[14],"VAR04");
            strcpy(memory_cells[15],"VAR07");
            break;

        case MUL:
            strcpy(memory_cells[0],"NOP##");                   ///    this is an empty cell with no opcode or operand
            strcpy(memory_cells[1],"LOD13");                   ///    this cell tells to load from 13
            strcpy(memory_cells[2],"MUL14");                   ///    this cell tells to multiply data in 14 from ALUX
            strcpy(memory_cells[3],"STO16");                   ///    this cell tells to store in 15
            strcpy(memory_cells[4],"LOD13");                   ///    this cell tells to add data in address 13 to the accumulator
            strcpy(memory_cells[5],"MUL14");
            strcpy(memory_cells[6],"MLX15");                   ///    this cell tells to multiply data in address 15 to the accumulator
            strcpy(memory_cells[7],"STO17");
            strcpy(memory_cells[9],"HLT##");
            strcpy(memory_cells[13],"VAR11");
            strcpy(memory_cells[14],"VAR02");
            strcpy(memory_cells[15],"VAR04");
            break;

        case DIV:
            strcpy(memory_cells[0],"NOP##");                   ///    this is an empty cell with no opcode or operand
            strcpy(memory_cells[1],"LOD13");                   ///    this cell tells to load from 13
            strcpy(memory_cells[2],"DIV14");                   ///    this cell tells to subtract data in 14 from ALUX
            strcpy(memory_cells[3],"STO16");                   ///    this cell tells to store in 15
            strcpy(memory_cells[4],"LOD13");                   ///    this cell tells to add data in address 13 to the accumulator
            strcpy(memory_cells[5],"DIV14");
            strcpy(memory_cells[6],"DVX15");                   ///    this cell tells to divide data in address 15 to the accumulator
            strcpy(memory_cells[7],"STO17");
            strcpy(memory_cells[9],"HLT##");
            strcpy(memory_cells[13],"VAR16");
            strcpy(memory_cells[14],"VAR02");
            strcpy(memory_cells[15],"VAR03");
            break;

        case INFJMP:
            strcpy(memory_cells[0],"NOP##");                   ///    this is an empty cell with no opcode or operand
            strcpy(memory_cells[1],"LOD13");                   ///    this cell tells to load from 13
            strcpy(memory_cells[2],"DIV14");                   ///    this cell tells to divide data in 14 from ALUX
            strcpy(memory_cells[3],"STO16");                   ///    this cell tells to store in 16
            strcpy(memory_cells[4],"JMP01");                   ///    this cell tells jump back to 1 [WARNING: THIS IS A RECURSIVE LOOP]
            strcpy(memory_cells[5],"LOD13");
            strcpy(memory_cells[6],"ADD15");
            strcpy(memory_cells[7],"STO17");
            strcpy(memory_cells[9],"HLT##");
            strcpy(memory_cells[13],"VAR16");
            strcpy(memory_cells[14],"VAR02");
            strcpy(memory_cells[15],"VAR03");
            break;

        case CPY:
            strcpy(memory_cells[0],"NOP##");                   ///    this is an empty cell with no opcode or operand
            strcpy(memory_cells[1],"CPY1011");                 ///    this cell tells to copy contents of address 10 to address 11
            strcpy(memory_cells[2],"CPY1112");                 ///    this cell tells to copy contents of address 11 to address 12
            strcpy(memory_cells[3],"LOD12");                   ///    this cell tells to load from 12
            strcpy(memory_cells[4],"ADD13");                   ///    this cell tells to add from address 13
            strcpy(memory_cells[5],"STO14");                   ///    this cell tells to store to address 14
            strcpy(memory_cells[6],"CPY1415");                 ///    this cell tells to copy contents of address 14 to address 15
            strcpy(memory_cells[7],"HLT##");
            strcpy(memory_cells[10],"VAR12");
            strcpy(memory_cells[13],"VAR16");
            break;

        case MOV:
            strcpy(memory_cells[0],"NOP##");                   ///    this is an empty cell with no opcode or operand
            strcpy(memory_cells[1],"MOV1011");                 ///    this cell tells to move contents of address 10 to address 11
            strcpy(memory_cells[2],"MOV1112");                 ///    this cell tells to move contents of address 11 to address 12
            strcpy(memory_cells[3],"LOD12");                   ///    this cell tells to load from 12
            strcpy(memory_cells[4],"ADD13");                   ///    this cell tells to add from address 13
            strcpy(memory_cells[5],"STO14");                   ///    this cell tells to store to address 14
            strcpy(memory_cells[6],"MOV1415");                 ///    this cell tells to move contents of address 14 to address 15
            strcpy(memory_cells[7],"HLT##");
            strcpy(memory_cells[10],"VAR12");
            strcpy(memory_cells[13],"VAR16");
            break;

        case EMPT:
            break;

        case USR:
            break;

        default:
            break;
    }


}


void::Memory::read(char instructionbus[], int addressbus) {
    strcpy(instructionbus, memory_cells[addressbus]);
}

void::Memory::write(char instructionbus[], int addressbus) {
    strcpy(memory_cells[addressbus], instructionbus);
}

char*::Memory::get_block(int i) {
    return memory_cells[i];
}

int::Memory::get_size() {
    return (sizeof(memory_cells)/sizeof(memory_cells[0]));
}

void::Memory::printmem() {
    for(int i = 0; i < get_size(); i++){
        cout << i << ": " << get_block(i) << endl;
    }
}

void::Memory::mem_input() {


    for(int p = 0; p < get_size(); p++){
        printmem();
        char input[8];
        cout << "Input for position: " << p << endl;
        cin >> input;
        strcpy(memory_cells[p], input);
    }

    cout << "Finished inputting" << endl;

}


//
// Created by Peter Chai on 31/03/2017.
//

