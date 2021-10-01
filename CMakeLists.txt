cmake_minimum_required(VERSION 3.20)
project(cpp_practise)

set(CMAKE_CXX_STANDARD 14)

# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

# Task 1
#add_executable(cpp_practise
#        solutions/Task1.cpp)

# Task 2
add_executable(cpp_practise
        solutions/Task2.cpp)

# Task 3
#add_executable(cpp_practise
#        Task2.cpp)

# Task 4
#add_executable(cpp_practise
#        Task2.cpp)

# Task 5
#add_executable(cpp_practise
#        Task2.cpp)
