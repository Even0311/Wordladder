cmake_minimum_required(VERSION 3.5)
project(6771wl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    CMakeLists.txt
        genlib.cpp
    genlib.h
    lexicon.cpp
    lexicon.h
    main.cpp
    strutils.cpp
    strutils.h)

add_executable(6771wl ${SOURCE_FILES})