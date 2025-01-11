@echo off
set C_INCLUDE_PATH=windows_build\include
windres windows_build\icon\my.rc -O coff -o windows_build\icon\my.res
if not exist bin mkdir bin
gcc src\*.c windows_build\icon\my.res -o bin\quixo.exe -Lwindows_build\lib -lncursesw -static -DNCURSES_STATIC