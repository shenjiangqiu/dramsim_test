cmake_minimum_required(VERSION 3.10)
project(test VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE  SOURCES *.cc)

add_executable(test  ${SOURCES})
target_link_libraries(test PUBLIC dramsim3 fmt Catch2)

