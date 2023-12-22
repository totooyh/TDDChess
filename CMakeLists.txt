cmake_minimum_required(VERSION 3.20)
project(chess3_0)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(lib/googletest-main)

