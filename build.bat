
@echo off
setlocal

:: Define build directory
set BUILD_DIR=build
set SHADERS_DIR=shaders

:: Clean previous build
echo Cleaning previous build...
if exist %BUILD_DIR% (
    rd /s /q %BUILD_DIR%
)

:: Create build directory
echo Creating build directory...
mkdir %BUILD_DIR% || (echo Failed to create build directory & exit /b 1)

:: Navigate to build directory
cd %BUILD_DIR%

:: Configure the project with CMake using MinGW
echo Configuring project...
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc .. || (echo CMake configuration failed! & exit /b %errorlevel%)

:: Build the project
echo Building project...
mingw32-make || (echo Build failed! & PAUSE & exit /b %errorlevel%)

:: Ensure shaders folder exists in build directory
echo Creating shaders folder in build directory...
mkdir %SHADERS_DIR% || (echo Failed to create shaders directory! & exit /b %errorlevel%)

:: Copy shaders folder contents into build/shaders
echo Copying shaders folder contents into build/shaders...
xcopy /E /I /Y ..\%SHADERS_DIR%\* %SHADERS_DIR%\ || (echo Failed to copy shaders folder contents! & exit /b %errorlevel%)

:: Done
echo Build complete.

:: Run the program if desired
:: echo Running program...
:: CSandbox.exe
:: drmemory -- CSandbox.exe

endlocal

