cmake_minimum_required(VERSION 3.10)
project(ResourceManagement)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Find threads package
find_package(Threads REQUIRED)

# Add source files
set(SOURCES
    src/main.cpp
    src/Investment.cpp
    src/FileDescriptor.cpp
    src/Lock.cpp
    src/ThreadedFileOps.cpp
)

# Create executable
add_executable(resource_manager ${SOURCES})

# Link threading library
target_link_libraries(resource_manager Threads::Threads)

# Include directories
target_include_directories(resource_manager PRIVATE src)

# Compiler warnings
if(MSVC)
    target_compile_options(resource_manager PRIVATE /W4)
else()
    target_compile_options(resource_manager PRIVATE -Wall -Wextra -pedantic)
endif()

# Print configuration
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")


