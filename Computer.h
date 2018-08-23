#ifndef COMPENGPROJ_COMPUTER_H
#define COMPENGPROJ_COMPUTER_H
#include "Memory.h"
#include "IO.h"
#include "CPU.h"

class Memory;
class CPU;

class Computer{

private:
    CPU *CPU1;
    Memory *Memory1;
//    IO IO1;

    char instructionbus[5];
    int addressbus = 0;

    bool shutdown = false;

public:

    Computer();
    void run();
    void fetch();
    void execute();
    void load_addressbus(int address);
    void ROM_out_instructionbus();

    void menu();

    char* get_instructionbus();
    int get_addressbus();

};

#endif //COMPENGPROJ_COMPUTER_H

//
// Created by Peter Chai on 03/04/2017.
//