cmake_minimum_required(VERSION 3.27)
project(lab7 C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)

add_executable(lab7
        src/main.c
        src/hash_table.c
        inc/hash_table.h
        inc/avl_tree.h
        inc/bst_tree.h
        inc/efficiency.h
        src/efficiency.c
        src/avl_tree.c
        src/bst_tree.c
        inc/ui.h
        src/ui.c)