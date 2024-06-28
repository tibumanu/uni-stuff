cmake_minimum_required(VERSION 3.24)
project(s2)

set(CMAKE_CXX_STANDARD 17)

add_executable(s2 main.cpp Song.h Duration.cpp Duration.h Song.cpp DynamicVector.cpp DynamicVector.h)
