project(pe_3)
cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 11)

add_executable(app src/app.cc src/workermi.cc)
target_include_directories(app PUBLIC include)