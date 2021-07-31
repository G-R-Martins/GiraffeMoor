@echo off

:: Change the color of the letters to yellow 
color 06

:: Window title
title Build GiraffeMoor 

:: Go to build directory
cd .\build

:: Build solution
cmake --build .


exit