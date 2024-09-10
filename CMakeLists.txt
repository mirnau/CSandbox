cmake_minimum_required(VERSION 3.10)
project(CSandbox C)

# Set the C standard
set(CMAKE_C_STANDARD 11)

# Set the default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Recursively find all source files
file(GLOB_RECURSE SOURCES "src/*.c")

# Define executable target
add_executable(CSandbox ${SOURCES})
