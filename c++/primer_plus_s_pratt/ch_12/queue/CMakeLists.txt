cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

#set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
#set(QUEUE_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/queue)

#include_directories(${QUEUE_HEADERS_DIR})

#add_subdirectory(src)
add_subdirectory(test)

#add_executable(queue main.cpp queue/Queue.cpp queue/Queue.h)