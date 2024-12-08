cmake_minimum_required(VERSION 3.27)
project(lab5 C)

set(CMAKE_C_STANDARD 11)
include_directories(inc)

add_executable(lab5
        src/main.c
        src/arr_queue.c
        src/list_queue.c
        inc/arr_queue.h
        inc/list_queue.h
        src/modeling.c
        inc/request.h
        inc/modeling.h
        inc/efficiency.h
        src/efficiency.c)
