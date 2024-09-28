cmake_minimum_required(VERSION 3.27)
project(lab2_1)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.0)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2_1 main.cpp
        smrt_ptr/Shared_ptr.h
        smrt_ptr/Weak_ptr.h
        smrt_ptr/Unique_ptr.h
        smrt_ptr/Control_Block.h
        sequence/Sequence.h
        sequence/ArraySequence.h
        sequence/LinkedListSequence.h
        sequence/LinkedList.h
        sequence/DynamicArray.h
        sequence/Common.h
  )

target_link_libraries(lab2_1 sfml-system sfml-window sfml-graphics sfml-audio)

add_subdirectory(Google_tests)
