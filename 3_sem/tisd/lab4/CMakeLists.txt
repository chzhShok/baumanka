cmake_minimum_required(VERSION 3.27)
project(lab4 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab4
        main.c
        errors.h
        stack_array.h
        stack_list.h
        stack_array.c
        stack_list.c
        time_stack.c
)
 