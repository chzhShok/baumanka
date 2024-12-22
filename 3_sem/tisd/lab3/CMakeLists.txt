cmake_minimum_required(VERSION 3.27)
project(lab3 C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)

add_executable(lab3
        src/main.c
        inc/matrix.h
        src/matrix.c
        inc/ui.h
        src/ui.c
        inc/efficiency.h
        src/efficiency.c
)
