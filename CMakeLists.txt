cmake_minimum_required(VERSION 3.27)
project(lab2_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2_1 main.cpp
        Shared_ptr.h
        Weak_ptr.h
        Unique_ptr.h
        Control_Block.h)
add_subdirectory(Google_tests)
