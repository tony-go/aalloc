#include <gtest/gtest.h>

#include "aalloc.h"

TEST(aalloc, init_region) {
  Region *r = init_region(1024);

  EXPECT_EQ(r->size, 1024);
  EXPECT_EQ(r->capacity, 0);
  EXPECT_NE(r->data, nullptr);
}

TEST(aalloc, alloc_region) {
  Region *r = init_region(1024);
  const char* string = "Hello, World!";
  const size_t str_size = strlen(string) + 1;

  char* alloc_str = (char*)alloc_region(r, str_size); 
  strcpy(alloc_str, string);

  EXPECT_STREQ(alloc_str, string);
  EXPECT_EQ(r->capacity, str_size);
}

TEST(aalloc, alloc_region_multiple) {
  Region *r = init_region(1024);

  const char* string = "Hello, World!";
  const size_t str_size = strlen(string) + 1;
  char* alloc_str = (char*)alloc_region(r, str_size); 
  strcpy(alloc_str, string);

  const char* string2 = "Hello, World! 2";
  const size_t str_size2 = strlen(string2) + 1;
  char* alloc_str2 = (char*)alloc_region(r, str_size2); 
  strcpy(alloc_str2, string2);

  EXPECT_STREQ(alloc_str, string);
  EXPECT_STREQ(alloc_str2, string2);
  EXPECT_EQ(r->capacity, str_size + str_size2);
}

TEST(aalloc, alloc_region_overflow) {
  const char* string = "Hello, World!";
  const size_t str_size = strlen(string) + 1;
  Region *r = init_region(str_size - 1);

  void* p = alloc_region(r, str_size);

  EXPECT_EQ(p, nullptr);
  EXPECT_EQ(r->capacity, 0);
}

TEST(aalloc, region_free) {
  Region *r = init_region(1024);

  const char* string = "Hello, World!";
  const size_t str_size = strlen(string) + 1;
  char* alloc_str = (char*)alloc_region(r, str_size); 
  strcpy(alloc_str, string);

  free_region(r);
  r = nullptr;
}

