#include <iostream>
#include <string.h>
#include "Computer.h"

#define DEBUGMODE 1

using namespace std;



Computer::Computer(){

    menu();
    delete CPU1;
    delete Memory1;

}

void::Computer::run() {

    CPU1->CPU_RELOAD();                                                                 /// Reset the values in the CPU like the PC and halt signal
                                                                                        /// Unnecessary due to CPU being deleted, however kept here in case of random values assigned to it
    cout << "========INITIAL MEMORY========" << endl;
    Memory1->printmem();                                                                /// Print the memory blocks out at the beginning
    cout << "==============================" << endl;
    while(CPU1->get_PC() < Memory1->get_size()){                                        /// Keep executing cycle until all the memory cells have been read
        if(!CPU1->Halt){                                                                /// Check if the halt signal has been given
            cout << "============================CYCLE" << CPU1->get_PC() << "============================" << endl;
            cout << "=======> 0: fetching..." << endl;
            fetch();
            cout << "=======> 1: executing..." << endl;
            execute();
            cout << "=======> 2: finished..." << endl;
            cout << "=============================================================" << endl;
        }
        else break;
    }
    cout << "Program Complete!" << endl;

    cout << "========FINAL MEMORY========" << endl;
    Memory1->printmem();                                                                /// Print the memory blocks out at the end
    cout << "==============================" << endl;
    return;
}

void::Computer::fetch() {

    addressbus = CPU1->update_address_bus(CPU1->get_PC());                              /// Generic update address function used to initial upload the PC
#if DEBUGMODE == 1
        cout << "0.1: Addressbus: " << addressbus << endl;
#endif

    Memory1->read(instructionbus,addressbus);
#if DEBUGMODE == 1
        cout << "0.2: Instructionbus: " << instructionbus << endl;
#endif

    CPU1->update(CPU1->READ,addressbus,instructionbus);
#if DEBUGMODE == 1
        cout << "0.3: MODE: ";
    if(CPU1->mode == CPU1->READ){
        cout<< "READ" << endl;
    }
    else cout << "WRITE" << endl;
        cout << "0.4: MAR: " << CPU1->get_MAR() << endl;
        cout << "0.5: MDR: " << CPU1->get_MDR() << endl;
#endif

    CPU1->IR_load();
#if DEBUGMODE == 1
        cout << "0.6: IR: " << CPU1->get_IR() << endl;
#endif
    return;
}

void::Computer::execute() {

    CPU1->IR_decode();
        #if DEBUGMODE == 1
        cout << "DECODING" << endl;
        cout << "1.1: IR: " << CPU1->get_IR() << endl;
        cout << "1.2: Opcode: " << CPU1->get_opcode() << endl;
        cout << "1.3: Operand: " << CPU1->get_operand1() << endl;
        cout << "1.4: Operand Cast: ";
        if (!strcmp(CPU1->get_opcode(),"NOP")) {cout << "is not available with No Operation" << endl;}
        else cout << CPU1->get_operand1_cast() << endl;
        cout << "1.5: This data " << (CPU1->yesOP ? "is " : "is not ") << "operable" << endl;
        cout << "1.6: There " << (CPU1->feedback ? "is " : "is no ") << "feedback" << endl;
        #endif
    if (CPU1->yesOP){                                                                                               /// If instruction is not NOP or VAR
        if (!CPU1->feedback){                                                                                       /// Does the instruction require feedback?
            if (!strcmp(CPU1->get_opcode(),"STO")) {                                                                /// This one is for store
                CPU1->CPU_execute();                                                                                /// Execute store
                    #if DEBUGMODE == 1
                    cout << "STORING" << endl;
                    cout << "1.7: Feedback Instruction: " << CPU1->get_feedback_instruction() << endl;
                    #endif

                CPU1->update(CPU1->WRITE, CPU1->get_operand1_cast(),CPU1->get_feedback_instruction());                  /// Update the MAR and MDR
                strcpy(instructionbus,CPU1->update_instructionbus(CPU1->get_MDR()));                                    /// Copy MDR to instructionbus, strcpy for char array
                addressbus = CPU1->update_address_bus(CPU1->get_MAR());                                                 /// Copy MAR to addressbus, assign int values
                    #if DEBUGMODE == 1
                    cout << "1.8: Writing " << instructionbus << " to address " << addressbus << endl;
                    #endif

                Memory1->write(instructionbus,addressbus);                                                              /// Write the instruction to memory location at address
                    #if DEBUGMODE == 1
                    cout << "1.9: Memory " << addressbus << " is now " << Memory1->get_block(addressbus) << endl;
                    #endif

                return;
            }
            else if (!strcmp(CPU1->get_opcode(), "JMP")) {                                                     /// This one is for jump
                CPU1->CPU_execute();
                    #if DEBUGMODE == 1
                    cout << "JUMPING" << endl;
                    cout << "1.7: Jumping to address " << CPU1->get_PC() << endl;
                    #endif
                return;
            }
            return;
        }
        else if (CPU1->feedback){                                                                           /// If instruction needs feedback, this is the routine
            addressbus = CPU1->update_address_bus(CPU1->get_operand1_cast());                                       /// Get the address to feedback from
            Memory1->read(instructionbus,addressbus);                                                               /// Read the data at feedback address
            CPU1->update(CPU1->READ,addressbus,instructionbus);                                                     /// update the MAR and MDR
                #if DEBUGMODE == 1
                cout << "GETTING VARIABLE FOR OPERATION: " << CPU1->get_opcode() << endl;
                cout << "1.7: Feedback Data in MDR: " << CPU1->get_MDR() << endl;
                #endif

            CPU1->MDR_decode();                                                                                     /// Decode the values in the MDR
            if (!strcmp(CPU1->get_MDR_opcode(),"VAR")) {                                                            /// Check the feedback is a variable
                if (!strcmp(CPU1->get_opcode(), "MOV") || !strcmp(CPU1->get_opcode(), "CPY")){                      /// In the special case that it's MOV or CPY
                    addressbus = CPU1->update_address_bus(CPU1->get_operand2_cast());
                    strcpy(instructionbus,CPU1->update_instructionbus(CPU1->get_MDR()));

                        #if DEBUGMODE == 1
                        cout << "1.8: Writing " << instructionbus << " to address " << addressbus << endl;
                        #endif

                    Memory1->write(instructionbus,addressbus);                                                      /// Write the instruction to memory location at address
                        #if DEBUGMODE == 1
                        cout << "1.9: Memory " << addressbus << " is now " << Memory1->get_block(addressbus) << endl;
                        #endif

                    if (!strcmp(CPU1->get_opcode(), "MOV")){
                        addressbus = CPU1->update_address_bus(CPU1->get_operand1_cast());
                        strcpy(instructionbus,"NOP##");                                                             /// Delete old memory location if MOV
                        Memory1->write(instructionbus,addressbus);
                    }
                }
                else {
                    CPU1->CPU_execute(CPU1->get_MDR_operand());                                                     /// If not MOV or CPY, then continue with other operations
                        #if DEBUGMODE == 1
                        cout << "1.8: ALU Contents: " << CPU1->get_feedback_instruction() << endl;
                        CPU1->print_ALU();
                        #endif

                    CPU1->clearXY();                                                                                    /// Clear ALU X and Y;
                }
                return;
            }
            else cout << "error, feedback address is not a variable!" << endl;
        }
    }
    return;

}

void::Computer::menu() {

    int choice;
    int example;

    while(!shutdown) {

        cout << "========MENU========" << endl;
        cout << "1: Run Examples" << endl;
        cout << "2: Input Memory" << endl;
        cout << "3: Shutdown" << endl;

        cin >> choice;

        if (choice == 1) {
            cout << "========EXAMPLES========" << endl;
            cout << "1: ADD" << endl;                                           /// See the constructor in Memory.cpp for more information
            cout << "2: SUBTRACT" << endl;
            cout << "3: JUMP" << endl;
            cout << "4: MODULO" << endl;
            cout << "5: MULTIPLY" << endl;
            cout << "6: DIVIDE" << endl;
            cout << "7: INFINITE JUMP" << endl;
            cout << "8: COPY" << endl;
            cout << "9: MOVE" << endl;
            cout << "10: USER DEFINED" << endl;

            cin >> example;

            switch (example) {

                case 1:
                    CPU1 = new CPU;
                    Memory1 = new Memory(Memory1->ADD);                         /// You can see that it creates a pointer to a new memory loaded with an example
                    run();
                    delete Memory1;
                    delete CPU1;
                    break;
                case 2:
                    CPU1 = new CPU;
                    Memory1 = new Memory(Memory1->SUB);
                    run();
                    delete Memory1;
                    delete CPU1;
                    break;
                case 3:
                    CPU1 = new CPU;
                    Memory1 = new Memory(Memory1->JMP);
                    run();
                    delete Memory1;
                    delete CPU1;
                    break;
                case 4:
                    CPU1 = new CPU;
                    Memory1 = new Memory(Memory1->MOD);
                    run();
                    delete Memory1;
                    delete CPU1;
                    break;
                case 5:
                    CPU1 = new CPU;
                    Memory1 = new Memory(Memory1->MUL);
                    run();
                    delete Memory1;
                    delete CPU1;
                    break;
                case 6:
                    CPU1 = new CPU;
                    Memory1 = new Memory(Memory1->DIV);
                    run();
                    delete Memory1;
                    delete CPU1;
                    break;
                case 7:
                    CPU1 = new CPU;
                    Memory1 = new Memory(Memory1->INFJMP);
                    run();
                    delete Memory1;
                    delete CPU1;
                    break;
                case 8:
                    CPU1 = new CPU;
                    Memory1 = new Memory(Memory1->CPY);
                    run();
                    delete Memory1;
                    delete CPU1;
                    break;
                case 9:
                    CPU1 = new CPU;
                    Memory1 = new Memory(Memory1->MOV);
                    run();
                    delete Memory1;
                    delete CPU1;
                    break;
                case 10:
                    CPU1 = new CPU;
                    run();
                    delete Memory1;
                    delete CPU1;
                    break;
                default:
                    cout << "You did not enter a valid option" << endl;
                    break;

            }
        }

        else if (choice == 2){
            Memory1 = new Memory(Memory1->USR);
            Memory1->mem_input();
            cout << "Now try to run User Defined in examples" << endl;
        }
        else if (choice == 3){
            shutdown = true;
            cout << "Shutdown Selected..." << endl;
        }
    }
    cout << "Shutting down..." << endl;
    return;


}

//
// Created by Peter Chai on 03/04/2017.
//