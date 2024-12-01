cmake_minimum_required(VERSION 3.27)
project(lab6 C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)

add_executable(lab6
        inc/efficiency.h
        inc/tree.h
        src/efficiency.c
        src/main.c
        src/tree.c)
