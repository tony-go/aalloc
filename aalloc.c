#include "aalloc.h"

#include <assert.h>
#include <mm_malloc.h>

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
