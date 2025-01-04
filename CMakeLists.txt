cmake_minimum_required(VERSION 3.10)

project(train_cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MAIN main)

add_executable(${MAIN} main.cpp)

target_link_libraries(${MAIN} PRIVATE cpp17)

add_subdirectory(src)