cmake_minimum_required(VERSION 3.5.1)    # CMake version check
project(ch_13_pe_1)                     # Create project "simple_example"
set(CMAKE_CXX_STANDARD 11)              # Enable c++11 standard


add_executable(exec src/dma.cc src/main.cc)
target_include_directories(exec PUBLIC include)
