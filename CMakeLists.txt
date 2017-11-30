cmake_minimum_required(VERSION 3.8)
project(cs449assignment5)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES myshell.c)
add_executable(cs449assignment5 ${SOURCE_FILES})