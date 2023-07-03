#include "aalloc.h"

#include <assert.h>
#include <mm_malloc.h>

Arena* _new_arena(size_t size) {
  Arena *arena = malloc(sizeof(Arena) + size);

  arena->size = size;
  arena->used = 0;
  arena->data = (void*)(arena + 1);
  arena->next = NULL;

  return arena;
}

Arena *new_arena() {
  return _new_arena(ARENA_PAGE_SIZE);
}

void *alloc_arena(Arena *arena, size_t size) {
  if (size + arena->used > arena->size) {
    size_t next_size = size > ARENA_PAGE_SIZE ? size : ARENA_PAGE_SIZE;
    arena->next = _new_arena(next_size);
    return arena->next->data;
  }
  void *ptr = arena->data + arena->used;
  arena->used = arena->used + size;
  return ptr;
}

Region *init_region(size_t size) {
  Region *region = malloc(sizeof(Region) + size);
  assert(region != NULL);

  region->size = size;
  region->used = 0;
  // NOTE: initialize data pointer to the first byte after the Region struct
  region->data = (void *)(region + 1);

  return region;
}

void *alloc_region(Region *region, size_t size) {
  if (region->used + size > region->size) {
    return NULL;
  }

  void *ptr = region->data + region->used;
  region->used += size;

  return ptr;
}

void free_region(Region *region) { free(region); }
