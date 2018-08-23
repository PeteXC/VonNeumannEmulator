cmake_minimum_required(VERSION 3.6)
project(CompEngProj)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp CPU.cpp Memory.cpp IO.cpp IO.h CPU.h Memory.h Computer.cpp Computer.h)
add_executable(CompEngProj ${SOURCE_FILES})