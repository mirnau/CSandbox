@echo off
setlocal

:: Define build directory
set BUILD_DIR=build
set SRC_GRAPHICS=src\graphics

:: Clean previous build
echo Cleaning previous build...
if exist %BUILD_DIR% (
    rd /s /q %BUILD_DIR%
)

:: Create build directory
echo Creating build directory...
mkdir %BUILD_DIR%

:: Navigate to build directory
cd %BUILD_DIR%

:: Configure the project with CMake using Ninja
echo Configuring project...

cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc ..

:: Check if CMake configuration was successful
if %errorlevel% neq 0 (
    echo CMake configuration failed!
    exit /b %errorlevel%
)

:: Build the project
echo Building project...
mingw32-make

:: Check if build was successful
if %errorlevel% neq 0 (
    echo Build failed!
    exit /b %errorlevel%
)


:: Copy .cso files to the build directory if they exist
echo Copying .cso files...
if exist %SRC_GRAPHICS%\*.cso (
    copy /y %SRC_GRAPHICS%\*.cso %BUILD_DIR%\
)


:: Done
echo Build complete.

endlocal

PAUSE
