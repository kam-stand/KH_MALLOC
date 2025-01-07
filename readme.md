# Simple Malloc Library

This is a simple library to implement the functionality of `malloc` using `mmap`. This project is meant to be a learning process.

## Header File

The header file `mem_lib.h` contains all of the function prototypes for the library.

## Functions to Implement

The main functions to implement in this library are:

- [x] `HEAP_ALLOC(size_t req)`: Allocates a block of memory of the requested size.
- [x] `HEAP_FREE(void *ptr)`: Frees the previously allocated memory block pointed to by `ptr`.
- [ ] `HEAP_REALLOC(void *ptr, size_t resize)`: Resizes a previously allocated memory block.
- [ ] `HEAP_GROW()`: Grows the heap if original is out of space
## Running the Program

To run the program, follow these steps:

1. Clone the repository:

   ```bash
   git clone https://github.com/kam-stand/KH_MALLOC.git
   ```

2. Change into the root directory:

   ```bash
   cd SIMPLE_MALLOC
   ```

3. Make the `run.sh` script executable:

   ```bash
   chmod +x run.sh
   ```

4. Run the script:
   ```bash
   ./run.sh
   ```

## Arena Allocator

There is a folder called `arena_allocator` that is used as inspiration and sometimes serves as base-level logic to implement certain functions like `merge` and `free` in a much more simplified manner.
