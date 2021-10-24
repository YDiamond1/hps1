cmake_minimum_required(VERSION 3.18)
project(lab1 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab1 main.c algs/alg_smooth.c algs/alg_smooth.h list/list.c list/list.h algs/algs_shell.c algs/algs_shell.h merge_sort.c merge_sort.h)

find_package(OpenMP)
if(OpenMP_FOUND)
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()