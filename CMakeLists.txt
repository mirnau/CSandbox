cmake_minimum_required(VERSION 3.10)
project(CSandbox C)

# Set the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Set the default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Recursively find all source files
file(GLOB_RECURSE SOURCES "src/*.c")

# Define executable target
add_executable(CSandbox ${SOURCES})

# Specify the DirectX SDK directory (adjust if needed)
set(DIRECTX_SDK_DIR "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)")

# Include DirectX headers
include_directories(${DIRECTX_SDK_DIR}/Include)

# Link against DirectX 11 libraries
target_link_libraries(CSandbox
    d3d11.lib
    d3dcompiler.lib
    dxgi.lib
    ${CMAKE_SOURCE_DIR}/vendor/nuklear/libnuklear.lib
)

# Specify the DirectX SDK lib directory (adjust if needed)
link_directories(${DIRECTX_SDK_DIR}/Lib/x64)


# For MSVC compiler, specify additional flags
if(MSVC)
    add_compile_options(/W4 /WX) # Enable all warnings and treat them as errors
endif()
