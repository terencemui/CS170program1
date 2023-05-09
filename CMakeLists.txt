cmake_minimum_required(VERSION 3.10)
project(8puzzle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(solve State.cpp main.cpp)