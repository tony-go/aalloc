FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_executable(aalloc_test
               aalloc_test.cc)
target_link_libraries(aalloc_test
                      PRIVATE
                      aalloc
                      gtest_main)

gtest_discover_tests(aalloc_test)

