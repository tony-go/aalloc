#include "aalloc.h"

#include <mm_malloc.h>
#include <assert.h>

Region *init_region(size_t size) {
  Region *region = malloc(sizeof(Region) + size);
  assert(region);
 
  region->size = size;
  region->capacity = 0;
  region->data = (void*)(region + 1);

  return region;
}

void* alloc_region(Region *region, size_t size) {
  if (region->capacity + size > region->size) {
    return NULL;
  }
  
  void *ptr = region->data + region->capacity;

  region->capacity += size;

  return ptr;
}

void free_region(Region *region) {
  free(region);
}
