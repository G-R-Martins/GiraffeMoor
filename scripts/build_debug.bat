@echo off

:: Change the color of the letters to yellow 
color 06

:: Window title
title Compile DEBUG mode

:: Create directory to build the solution and projects
cd ..\build

:: Build GiraffeMoor
cmake --build . --config Debug

exit