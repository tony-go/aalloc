#ifndef AALLOC_LIB
#define AALLOC_LIB

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  void *data;
  size_t size;
  size_t capacity;
} Region;

Region *init_region(size_t capacity);

void free_region(Region *region);

void *alloc_region(Region *region, size_t size);

#ifdef __cplusplus
}
#endif

#endif
