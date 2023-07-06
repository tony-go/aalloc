# AAlloc

AAlloc is a custom memory allocator developed as a C library.
It provides a convenient way to allocate and deallocate memory regions of custom sizes.

## Getting Started

These instructions will get you a copy of the project up
and running on your local machine for development and testing purposes.

### Prerequisites

To build this project, you'll need:

* A C/C++ compiler
* CMake

### Building

Here are the steps to build the project:

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/aalloc.git
   cd aalloc
   ```

2. Create a `dist` directory and navigate into it:
   ```bash
   mkdir dist
   cd dist
   ```

3. Build the project:
   ```bash
   make
   ```

### Testing

When you'll run the `make` command, tests will be executed, but you can run them only:

```bash
make test
```

## Usage

AAlloc provides the following API to allocate and deallocate memory:

### `Arena *new_arena();`
Create a new Arena.

### `void *alloc_arena(Arena *arena, size_t size);`
Allocates a region of memory from the specified region. Returns a pointer to the allocated memory.

### `void free_arena(Arena *arena);`
Frees the specified region of memory.

## Example

```c
#include "aalloc.h"

// Create Arena
Arena *a = new_arena();

// Allocate memory and use the returned pointer
// to store your data.
void *ptr_a = alloc_arena(a, 512);
void *ptr_b = alloc_arena(a, 512);
void *ptr_c = alloc_arena(a, 512);

// Free the whole region.
free_arena(a);
a = nullptr;
```

## Contributing

If you have suggestions for how AAlloc could be improved, or want to report a bug, open an issue! Contributions of all kinds are welcomed!

## License

MIT © Tony Gorez
