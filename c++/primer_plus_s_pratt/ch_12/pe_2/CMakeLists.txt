cmake_minimum_required(VERSION 3.13)  # CMake version check
project(string_lib)          # Create project "simple_example"
set(CMAKE_CXX_STANDARD 98)            # Enable c++14 standard

add_executable(test src/test.cc src/string2.cc)
target_include_directories(test PUBLIC include)
