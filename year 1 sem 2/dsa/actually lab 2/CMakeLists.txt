cmake_minimum_required(VERSION 3.24)
project(actually_lab_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(actually_lab_2
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        IteratedList.cpp
        IteratedList.h
        ListIterator.cpp
        ListIterator.h
        ShortTest.cpp
        ShortTest.h node.cpp node.h)
