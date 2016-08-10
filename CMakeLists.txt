cmake_minimum_required(VERSION 3.1)
project(HPC-arena)

set(CMAKE_CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED TRUE)

file(GLOB SRC_FILES src/*.cpp)
include_directories(".")

add_executable(arena ${SRC_FILES})

#install(TARGETS HPC-arena DESTINATION bin)
