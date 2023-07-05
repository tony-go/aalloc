#include "aalloc.h"

#include <assert.h>
#include <mm_malloc.h>

Arena* _new_arena(size_t size) {
  Arena *arena = malloc(sizeof(Arena) + size);

  arena->size = size;
  arena->used = 0;
  // NOTE: initialize data pointer to the first byte after the Arena struct
  arena->data = (void*)(arena + 1);
  arena->next = NULL;

  return arena;
}

Arena *new_arena() {
  return _new_arena(ARENA_PAGE_SIZE);
}

void *alloc_arena(Arena *arena, size_t size) {
  Arena *last;

  do {
    if (size + arena->used <= arena->size) {
      void *ptr = arena->data + arena->used;
      arena->used = arena->used + size;
      return ptr;
    }

    last = arena;
    arena = arena->next;
  } while (NULL != arena);

  size_t next_size = size > ARENA_PAGE_SIZE ? size : ARENA_PAGE_SIZE;
  last->next = _new_arena(next_size);
  last->next->used += size;
  return last->next->data;
}

void free_arena(Arena *arena) { free(arena); }
