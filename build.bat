@echo off

:: Change the color of the letters to yellow 
color 06

:: Window title
title CMake setup for GiraffeMoor

:: Create directory to build the solution and projects
md build & cd .\build

:: Run CMake:
cmake .. -DCMAKE_CONFIGURATION_TYPES="Debug;Release" -DMKL_INTERFACE=lp64

:: Ask if should open the solution file
set /p inputOpt= "Type [Y] and hit enter to open Visual Studio solution, or just hit enter to finish "
if /i "%inputOpt:~,1%" EQU "y" start .\GiraffeMoor.sln 

exit