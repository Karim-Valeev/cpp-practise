cmake_minimum_required(VERSION 3.20)
project(cpp_practise)

set(CMAKE_CXX_STANDARD 14)

# for Open MP:
# added -fopenmp
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
#
#add_executable(cpp_practise
#        OpenMP/Task10.cpp)


include_directories(/usr/include/mpi)

add_executable(cpp_practise MPI/Task9.cpp)

set(CMAKE_C_COMPILER "/usr/bin/mpicc")
set(CMAKE_CXX_COMPILER "/usr/bin/mpic++")

cmake_minimum_required(VERSION 3.6)