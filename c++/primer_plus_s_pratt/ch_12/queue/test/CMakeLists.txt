cmake_minimum_required(VERSION 3.14)
project(queue_test)

set(GTEST_SOURCE_DIR lib/googletest-release-1.8.1)

add_subdirectory(${GTEST_SOURCE_DIR})

include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})
#include_directories(${QUEUE_HEADER_DIR})

#Define your executable
add_executable(main src/test_queue.cpp src/queue/Queue.cpp src/queue/Queue.h)

#Link with GoogleTest
target_link_libraries(main gtest gtest_main)