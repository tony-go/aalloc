cmake_minimum_required(VERSION 3.21)

project(aalloc VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17) # GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

enable_testing()

include(FetchContent)

add_library(aalloc STATIC
            aalloc.c
            aalloc.h)

add_subdirectory(test)

