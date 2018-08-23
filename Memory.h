#ifndef COMPENGPROJ_MEMORY_H
#define COMPENGPROJ_MEMORY_H

#include <iostream>
#include "Computer.h"

using namespace std;

class Memory{

private:

    char memory_cells[18][8];


public:
    enum examples {ADD,SUB,JMP,MOD,DIV,MUL,INFJMP,CPY,MOV,EMPT,USR};
    examples example;

    Memory(examples example);

    void read(char[],int);
    char* read1(int);
    void write(char[],int);
    void printmem();
    void mem_input();

    char* get_block(int);
    int get_size();



};

#endif //COMPENGPROJ_MEMORY_H

//
// Created by Peter Chai on 03/04/2017.
//