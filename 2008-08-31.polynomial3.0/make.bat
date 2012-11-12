@echo off

echo start to compile all examples
echo.

cl /wd 4530 /wd 4996 /nologo  main.cpp term.cpp poly.cpp polynomial.cpp
echo.

del *.obj

echo done. bye.
pause
