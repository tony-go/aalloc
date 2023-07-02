cmake_minimum_required(VERSION 3.21)

project(aalloc VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17) # GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_library(aalloc STATIC
            aalloc.c
            aalloc.h)

enable_testing()
add_executable(aalloc_test
               aalloc_test.cc)
target_link_libraries(aalloc_test
                      PRIVATE
                      aalloc
                      gtest_main)
gtest_discover_tests(aalloc_test)

