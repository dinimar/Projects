cmake_minimum_required(VERSION 3.13)  # CMake version check
project(des_cypher_algorithm)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add des.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(simple_example ${SOURCE_FILES})
# Add include directory for header files
target_include_directories(test PUBLIC include)