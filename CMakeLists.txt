cmake_minimum_required(VERSION 3.24)
project(untitled2 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled2 main.c files_h/structs.h files_c/menu.c files_h/menu.h global.h global.c files_c/usuari.c files_h/usuari.h files_c/taulaHash.c files_h/taulaHash.h)
