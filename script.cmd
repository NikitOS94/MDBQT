@echo off
cls
flex %1
bison -dt %2
gcc %3 %4 -o %5