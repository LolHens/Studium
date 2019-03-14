cmake_minimum_required(VERSION 3.6)
project(Semester2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(semester2aufgabe1 aufgabe1.cpp)
add_executable(semester2aufgabe2 aufgabe2.cpp)
