cmake_minimum_required(VERSION 3.1)
project(HPC-arena)

set(CMAKE_CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED TRUE)

file(GLOB SRC_FILES src/*.cpp)
add_executable(arena ${SRC_FILES})

find_package(SFML COMPONENTS graphics window system)

include_directories("src")
include_directories(${SFML_INCLUDE_DIR})

target_link_libraries(arena ${SFML_LIBRARIES})
message(${SFML_INCLUDE_DIR})

#install(TARGETS HPC-arena DESTINATION bin)
