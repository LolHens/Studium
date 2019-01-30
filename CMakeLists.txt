cmake_minimum_required(VERSION 3.6)
project(Lerneinheit2)

set(CMAKE_CXX_STANDARD 14)

add_executable(aufgabe1 aufgabe1.cpp)
add_executable(aufgabe2 aufgabe2.cpp)
add_executable(aufgabe3 aufgabe3.cpp)
add_executable(aufgabe4 aufgabe4.cpp)
add_executable(aufgabe5 aufgabe5.cpp)
add_executable(aufgabe6 aufgabe6.cpp)
add_executable(aufgabe7 aufgabe7.cpp)
add_executable(munchtest munchtest.cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
