cmake_minimum_required(VERSION 3.24)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_HEADERS
        ExtendedTest.h
        Queue.h
        ShortTest.h)

set(PROJECT_SOURCES
        main.cpp
        ExtendedTest.h
        ShortTest.h
        )

add_executable(untitled main.cpp ExtendedTest.cpp ExtendedTest.h Queue.cpp Queue.h ShortTest.cpp ShortTest.h)
