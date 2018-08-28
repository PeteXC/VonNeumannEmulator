#include <iostream>
#include "IO.h"
#include "CPU.h"
#include "Memory.h"
#include "Computer.h"

using namespace std;

int main() {
    cout << "Starting Computer..." << endl;
    cout << "Time: " << __TIME__ << endl;
    cout << "Date: " << __DATE__ << endl << endl;
    cout << "Welcome to the Von Neumann Architecture Computer Emulator" << endl << endl;


    Computer *Computer1;
    Computer1 = new Computer;
    delete Computer1;
    cout << "Computer has shutdown" << endl;

    return 0;
}

//    Created by Peter Chai on 03/4/2016
//    Copyright © 2018, All Rights Reserved
