#ifndef AALLOC_LIB
#define AALLOC_LIB

#include <stddef.h>

#define ARENA_PAGE_SIZE 4096

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Arena Arena;

struct Arena {
  void *data;
  size_t size;
  size_t used;
  Arena *next;
};

Arena *new_arena();

void *alloc_arena(Arena *arena, size_t size);

typedef struct {
  void *data;
  size_t size;
  size_t used;
} Region;

Region *init_region(size_t capacity);

void free_region(Region *region);

void *alloc_region(Region *region, size_t size);

#ifdef __cplusplus
}
#endif

#endif
