cmake_minimum_required(VERSION 3.20)
project(cpp_practise)

set(CMAKE_CXX_STANDARD 14)

# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

add_executable(cpp_practise
        OpenMP/Task10.cpp)
