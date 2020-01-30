cmake_minimum_required(VERSION 3.12)  # CMake version check
project(string_lib)          # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

add_executable(test src/test.cc src/simulation.cc src/customer.cc)
target_include_directories(test PUBLIC include)