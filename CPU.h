#ifndef COMPENGPROJ_CPU_H
#define COMPENGPROJ_CPU_H

#include "Computer.h"

class CPU{
private:
    int PC = 0;

    char IR[8];                                         /// Instruction Register  [OPCODE:3]+[OPERAND:2]+[OPERAND:2]+'\0' = Requires 8 characters
    char operand1[8];                                   /// Splitting up the IR into parts for access
    char operand2[8];
    char opcode[8];                                     /// Note: The opcode and operand parts are longer arrays due to strncpy copy nature
    int operand1_cast;                                  /// Cont... They were made to be 8 characters long and in the CPP file a '\0' was put to end the string
    int operand2_cast;

    char MDR[8];                                        /// MDR Register
    int MAR;                                            /// MAR Register

    char MDR_opcode[8];                                 /// Splitting up the MDR register into parts for access.
    char MDR_operand1[8];
    int MDR_operand1_cast;

    char feedback_instruction[6];

    int ALU_X = 0;
    int ALU_Y = 0;
    int Accumulator = 0;



public:
    enum modes {READ,WRITE};
    modes mode;

    void CPU_RELOAD();

    void IR_load();
    int update_address_bus(int address);
    char* update_instructionbus(char instruction[]);
    char* feed_back_instruction(char* data_address, char* instruction);
    void IR_decode();
    void MDR_decode();
    void CPU_execute(int data);
    void CPU_execute();
    void clearXY();

    char* get_IR();                                                                             /// Get_ functions
    int get_PC();
    char* get_operand1();
    char* get_operand2();
    char*get_opcode();
    char*get_MDR_opcode();
    int get_MDR_operand();
    char* get_feedback_instruction();
    int get_operand1_cast();
    int get_operand2_cast();
    char*get_MDR();
    int get_MAR();

    void print_ALU();

    bool feedback;
    bool yesOP = true;
    bool Halt = false;

    int jmp_cnt = 0;

    void update(modes modes1, int address);
    void update(modes modes1, int address, char data[]);


};

#endif //COMPENGPROJ_CPU_H

//
// Created by Peter Chai on 03/04/2017.
//