@echo off
echo Compiling DSA Program...
gcc -c prime.c -lgmp
gcc -c generator.c -lgmp
gcc -c dsa.c -lgmp
gcc -c main.c -lgmp
gcc main.o prime.o generator.o dsa.o -o dsa_program.exe -lgmp
if %errorlevel% equ 0 (
    echo Build successful!
    echo Run with: dsa_program.exe
) else (
    echo Build failed!
)