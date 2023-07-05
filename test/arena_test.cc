#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string.h>

#include "../aalloc.h"

using ::testing::StartsWith;

// HELPERS
int count_arnea(Arena *a);
char *generate_string(size_t size, char filler);

TEST(aalloc, new_arena) {
  Arena *a = new_arena();

  EXPECT_EQ(a->size, ARENA_PAGE_SIZE);
  EXPECT_EQ(a->used, 0);
  EXPECT_NE(a->data, nullptr);
  EXPECT_EQ(a->next, nullptr);

  free_arena(a);
  a = nullptr;
}

TEST(aalloc, alloc_arena_return_ptr) {
  Arena *a = new_arena();
  const char *input = "hi";
  const size_t input_len = strlen(input) + 1;
 
  void *ptr = alloc_arena(a, input_len);

  EXPECT_NE(ptr, nullptr);

  free_arena(a);
  a = nullptr;
}

TEST(aalloc, alloc_arena_used_increase) {
  Arena *a = new_arena();
  const char *input = "hi";
  const size_t input_len = strlen(input) + 1;
 
  void *ptr = alloc_arena(a, input_len);

  EXPECT_EQ(a->used, input_len);

  free_arena(a);
  a = nullptr;
}

TEST(aalloc, alloc_arena_allocate_when_overflow) {
  Arena *a = new_arena();
  const size_t too_large_size = ARENA_PAGE_SIZE * 2;
  char *too_large_str = generate_string(too_large_size, 'x');

  char *ptr = (char *)alloc_arena(a, too_large_size);

  EXPECT_NE(ptr, nullptr);
  strcpy(ptr, too_large_str);
  EXPECT_STREQ(ptr, too_large_str);

  free_arena(a);
  a = nullptr;
}

TEST(aalloc, alloc_arena_use_available_memory) {
  Arena *a = new_arena();
  int count;

  char *str1 = generate_string(ARENA_PAGE_SIZE - 1, '1');
  char *str1_ptr = (char *)alloc_arena(a, ARENA_PAGE_SIZE - 1);
  strcpy(str1_ptr, str1);

  count = count_arnea(a);
  EXPECT_EQ(count, 1);

  char *str2 = generate_string(200, '2');
  char *str2_ptr = (char *)alloc_arena(a, 200);
  strcpy(str2_ptr, str2);

  count = count_arnea(a);
  EXPECT_EQ(count, 2);

  char *str3 = generate_string(ARENA_PAGE_SIZE - 1, '1');
  char *str3_ptr = (char *)alloc_arena(a, ARENA_PAGE_SIZE - 1);
  strcpy(str3_ptr, str3);

  count = count_arnea(a);
  EXPECT_EQ(count, 3);

  char *str4 = generate_string(200, '2');
  char *str4_ptr = (char *)alloc_arena(a, 200);
  strcpy(str4_ptr, str4);

  count = count_arnea(a);
  EXPECT_EQ(count, 3);

  // Check that values are still there
  EXPECT_STREQ(str1_ptr, str1);
  EXPECT_THAT(str2_ptr, StartsWith(str2));
  EXPECT_STREQ(str3_ptr, str3);
  EXPECT_STREQ(str4_ptr, str4);

  free_arena(a);
  a = nullptr;
  free(str1);
  free(str2);
  free(str3);
  free(str4);
}

/*
* ////////////////////
* ////////////////////
* ///// HELPERS //////
* ////////////////////
* ////////////////////
*/

char *generate_string(size_t size, char filler) {
  char *str = (char *)malloc(size + 1);
  memset(str, filler, size);
  return str;
}

int count_arnea(Arena *a) {
  int count = 0;

  Arena* curr = a;
  do {
    count++;
    curr = curr->next;
  } while (nullptr != curr);

  return count;
}
