@echo off
REM Run CMake to configure the project
cmake .
if errorlevel 1 goto :error

REM Build the project
cmake --build .
if errorlevel 1 goto :error

REM Change to the bin directory
cd bin

REM Run the executable
my_executable.exe
if errorlevel 1 goto :error

REM Pause to view output
PAUSE
goto :eof

:error
echo Build or execution failed.
PAUSE
