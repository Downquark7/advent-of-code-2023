cmake_minimum_required(VERSION 3.22.1)
project(advent_of_code_2023 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -fno-omit-frame-pointer -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fno-omit-frame-pointer -g")

add_executable(advent_of_code_2023 main.c)
