cmake_minimum_required(VERSION 3.8)
project(Calculator_Solver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        Solver.h
        UnarySlot.h
        )

add_executable(Calculator_Solver ${SOURCE_FILES})