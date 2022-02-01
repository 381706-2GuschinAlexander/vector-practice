cmake_minimum_required(VERSION 3.15)
project("Math-optimization" LANGUAGES CXX)

find_package(OpenMP REQUIRED)

add_executable(main main.cpp)
target_include_directories(main PRIVATE ../../${mincl})
target_link_libraries(main PRIVATE ${mlib} OpenMP::OpenMP_CXX)