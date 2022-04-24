#!/bin/bash

if ! command -v g++ &> /dev/null
then
    echo "g++ could not be found"
    echo "g++ will be installed"
    brew install gcc
    exit
fi
g++ -o emulator Computer.cpp CPU.cpp IO.cpp Memory.cpp main.cpp