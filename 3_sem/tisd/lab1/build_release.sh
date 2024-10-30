#!/bin/bash

gcc-13 -c main.c arithmetic.c long_nums_funcs.c -Werror -Wall -std=c99 -Wpedantic -O2 -Wextra -Wfloat-conversion -Wfloat-equal
gcc-13 *.o -o app.exe -lm
