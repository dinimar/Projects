cmake_minimum_required(VERSION 3.12)  # CMake version check
project(queue_simulation)          # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

add_executable(test src/test.cc src/customer.cc src/simulation.cc src/mq_simulation.cc)
target_include_directories(test PUBLIC include)