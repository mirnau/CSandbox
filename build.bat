@echo off
setlocal

:: Define build directory
set BUILD_DIR=build

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

cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=clang ..
::..cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=clang ..

:: Check if CMake configuration was successful
if %errorlevel% neq 0 (
    echo CMake configuration failed!
    exit /b %errorlevel%
)

:: Build the project
echo Building project...
mingw32-make
::ninja
::
:: Check if build was successful
if %errorlevel% neq 0 (
    echo Build failed!
    exit /b %errorlevel%
)

:: Done
echo Build complete.

:: Run the program
echo Running program...
drmemory -- CSandbox.exe

endlocal
