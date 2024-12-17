cmake_minimum_required(VERSION 3.27)
project(lab8 C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)

add_executable(lab8
        src/main.c
        src/ui.c
        inc/ui.h
        inc/graph.h
        src/graph.c)
