cmake_minimum_required(VERSION 3.8)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES client.cpp)
add_executable(client ${SOURCE_FILES})

set(SOURCE_FILES server.cpp)
add_executable(server ${SOURCE_FILES})