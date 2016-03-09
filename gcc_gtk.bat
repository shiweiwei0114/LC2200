@echo off
 
set gtk_ver=gtk+-3.0
pkg-config %gtk_ver% --cflags --libs >372project.txt
set /p pkg-info= <372project.txt
del 372project.txt
 
rem echo %pkg-info%
gcc main.c ALU.c Assembler.c FSM.c Memory.c Registers.c -o main.exe -Wall %pkg-info%