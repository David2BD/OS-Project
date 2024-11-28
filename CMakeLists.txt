cmake_minimum_required(VERSION 3.29)
project(ift_2001_tp3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ift_2001_tp3
    main.cpp
    MemoryManager.h
    MemorySegment.h
    Program.h
        MemoryManager.cpp
        Program.cpp
        cmake-build-debug/MemorySegment.cpp)
