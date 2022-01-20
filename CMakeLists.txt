cmake_minimum_required(VERSION 3.15)
project("Math-optimization" LANGUAGES CXX)

set(mlib mlib)
set(mincl src/mlib)

add_subdirectory(src/mlib)
add_subdirectory(src/main)
