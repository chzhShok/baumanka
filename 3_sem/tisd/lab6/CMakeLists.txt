cmake_minimum_required(VERSION 3.27)
project(lab6 C)

set(CMAKE_C_STANDARD 11)

include_directories(./inc)

add_executable(lab6
        src/main.c
        src/tree.c
        src/research.c
        inc/research.h
        inc/tree.h)
