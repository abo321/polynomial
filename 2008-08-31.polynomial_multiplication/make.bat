@echo off

echo start to compile all examples
echo.

cl /wd 4530 /wd 4996 /nologo polynomial1.cpp
cl /wd 4530 /wd 4996 /nologo polynomial2.cpp
cl /wd 4530 /wd 4996 /nologo polynomial3.cpp
echo.

del *.obj

echo done. bye.
pause
