cmake_minimum_required (VERSION 3.10.2)
project (ST-2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -g")


set(tool_dest "bin")
set(lib_dest "lib")
set(include_dest "include/")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(circle
    src/circle.cpp
    src/tasks.cpp
)
add_subdirectory(src)
add_subdirectory(test)
