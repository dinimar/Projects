cmake_minimum_required(VERSION 3.13)  # CMake version check
project(string_lib)          # Create project "simple_example"
set(CMAKE_CXX_STANDARD 98)            # Enable c++14 standard

add_executable(test src/usestock20.cc src/stock20.cc)
target_include_directories(test PUBLIC include)