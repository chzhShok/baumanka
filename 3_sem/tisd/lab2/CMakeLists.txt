cmake_minimum_required(VERSION 3.27)
project(lab2 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab2
        main.c
        subscriber_funcs.h
        subscriber_funcs.c
        original_table_funcs.c
        key_table_funcs.h
        key_table_funcs.c
        original_table_funcs.h
        time_sorts.c
        time_sorts.h)
