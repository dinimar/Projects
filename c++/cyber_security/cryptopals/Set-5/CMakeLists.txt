cmake_minimum_required(VERSION 3.5)     # CMake version check
project(des_cypher_algorithm)           # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)              # Enable c++14 standard
enable_testing()

# Add des.cpp file of project root directory as source file
set(SOURCE_FILES src/main.cc src/diffie-hellman.cc)

# Add executable target with source files listed in SOURCE_FILES variable
# add_executable(simple_example ${SOURCE_FILES})
# Add include directory for header files
# target_include_directories(test PUBLIC include)

# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()

# replace XX with the version you have
# set(Boost_ADDITIONAL_VERSIONS "1.58" "1.58.0")

# finds boost, triggers an error otherwise
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(Boost 1.58 REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(exec ${SOURCE_FILES})
target_include_directories(exec PUBLIC include)
target_link_libraries(exec ${OPENSSL_LIBRARIES})
# target_link_libraries(${PROJECT_NAME} ${OPENSSL_CRYPTO})

# creates the executable
# add_executable(test_executable test/test_des.cc src/des.cc)
# # indicates the include paths
# target_include_directories(test_executable PRIVATE ${Boost_INCLUDE_DIRS})
# target_include_directories(test_executable PUBLIC include)
# # indicates the shared library variant
# target_compile_definitions(test_executable PRIVATE "BOOST_TEST_DYN_LINK=1")
# # indicates the link paths
# target_link_libraries(test_executable ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

# # declares a test with our executable
# add_test(NAME test_des COMMAND test_executable)