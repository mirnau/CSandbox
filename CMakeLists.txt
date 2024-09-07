cmake_minimum_required(VERSION 3.10)
project(CSandbox C)

# Set output directories for binaries and objects
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set the object files output directory
set(CMAKE_OBJECT_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin-int)

# Specify C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Configure build types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "" FORCE)
set(CMAKE_BUILD_TYPE Debug) # Default build type

# Add source files
file(GLOB_RECURSE SOURCES "src/*.c")

# Create an executable target with WIN32 to indicate a GUI application
add_executable(my_executable WIN32 ${SOURCES})

# Set compiler flags for different build types
target_compile_options(my_executable PRIVATE
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Dist>:-O3 -DNDEBUG>
)

# Link libraries if needed
# target_link_libraries(my_executable some_library)

# Install target (optional)
# install(TARGETS my_executable DESTINATION bin)
