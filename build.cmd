@echo off
set C_INCLUDE_PATH=include
windres winbuild\my.rc -O coff -o winbuild\my.res
gcc src\*.c winbuild\my.res -o bin\main.exe -Llib -lncursesw