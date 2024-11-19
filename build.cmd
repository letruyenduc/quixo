@echo off
set C_INCLUDE_PATH=include
gcc src\*.c -o bin\main.exe -Llib -lncursesw