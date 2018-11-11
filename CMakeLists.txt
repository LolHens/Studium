cmake_minimum_required(VERSION 3.6)
project(Lerneinheit2)

set(CMAKE_CXX_STANDARD 14)

add_executable(aufgabe1 aufgabe1.cpp)
add_executable(aufgabe2 aufgabe2.cpp)
add_executable(aufgabe3 aufgabe3.cpp)
add_executable(aufgabe4 aufgabe4.cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
