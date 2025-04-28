cmake_minimum_required(VERSION 3.10)

# Project Name
project(TCPStack)

# Specify C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header directory
include_directories(include)

# Add all source files
file(GLOB_RECURSE SOURCES 
    src/*.cpp
    utils/*.cpp
)

# Create the executable
add_executable(tcp_stack ${SOURCES})