cmake_minimum_required(VERSION 3.20)
project(Dlopen)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(../Fibonacci Fibonacci)

add_executable(Dlopen main.cpp Dlopen.cpp)
