@echo off

:: Change the color of the letters to yellow 
color 06

:: Window title
title Generate and build GiraffeMoor

:: Create directory to build the solution and projects
md build & cd .\build

:: Generate project
cmake .. 
echo.
echo ==========================================================
echo.
:: Build GiraffeMoor
cmake --build .

exit