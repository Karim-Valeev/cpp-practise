cmake_minimum_required(VERSION 3.20)
project(cpp_practise)

set(CMAKE_CXX_STANDARD 14)

# for Open MP:
# added -fopenmp
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
#
#add_executable(cpp_practise
#        OpenMP/Task10.cpp)


# for MPI:
find_package(MPI REQUIRED)
# Include MPI includes
include_directories(${MPI_INCLUDE_PATH})

add_executable(cpp_practise MPI/Task1.cpp)

# Link against MPI
target_link_libraries(cpp_practise ${MPI_LIBRARIES})

if (MPI_COMPILE_FLAGS)
    set_target_properties(cpp_practise PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif ()
if (MPI_LINK_FLAGS)
    set_target_properties(cpp_practise PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif ()
