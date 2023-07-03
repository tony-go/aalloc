#include <gtest/gtest.h>
#include <string.h>
#include <sys/_types/_size_t.h>

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
