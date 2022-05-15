cmake_minimum_required(VERSION 3.15)
project(gseditor CXX)

# C++20 support
add_definitions("-std=c++20")

# Main source files
aux_source_directory(src SRC_LIST)

# Includes
include_directories(include)

# Executable
add_executable(${PROJECT_NAME} ${SRC_LIST})