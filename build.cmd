@echo off
set C_INCLUDE_PATH=include
clang src\*.c -o bin\main.exe -Llib -lncursesw