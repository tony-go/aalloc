#include <gtest/gtest.h>
#include <string.h>

#include "../aalloc.h"

TEST(aalloc, new_arena) {
  Arena *a = new_arena();

  EXPECT_EQ(a->size, ARENA_PAGE_SIZE);
  EXPECT_EQ(a->used, 0);
  EXPECT_NE(a->data, nullptr);
  EXPECT_EQ(a->next, nullptr);
}

TEST(aalloc, alloc_arena_return_ptr) {
  Arena *a = new_arena();
  const char *input = "hi";
  const size_t input_len = strlen(input) + 1;
 
  void *ptr = alloc_arena(a, input_len);

  EXPECT_NE(ptr, nullptr);
}

TEST(aalloc, alloc_arena_used_increase) {
  Arena *a = new_arena();
  const char *input = "hi";
  const size_t input_len = strlen(input) + 1;
 
  void *ptr = alloc_arena(a, input_len);

  EXPECT_EQ(a->used, input_len);
}

TEST(aalloc, alloc_arena_allocate_when_overflow) {
  Arena *a = new_arena();
  const size_t too_large_size = ARENA_PAGE_SIZE * 2;
  const size_t too_large_str_size = too_large_size + 1;
  char *too_large_str = (char *)malloc(too_large_str_size);
  memset(too_large_str, 'x', too_large_size);

  char *ptr = (char *)alloc_arena(a, too_large_size);

  EXPECT_NE(ptr, nullptr);
  strcpy(ptr, too_large_str);
  EXPECT_STREQ(ptr, too_large_str);
}
