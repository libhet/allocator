cmake_minimum_required(VERSION 3.9)
project(allocator)

set(CMAKE_CXX_STANDARD 14)

add_executable(allocator main.cpp newdelete.h newdelete.cpp my_forward_list.h)