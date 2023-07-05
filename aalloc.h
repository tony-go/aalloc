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

void free_arena(Arena *arena);

#ifdef __cplusplus
}
#endif

#endif
