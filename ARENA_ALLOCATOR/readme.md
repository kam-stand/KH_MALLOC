# ARENA ALLOCATORS
This is not a full or even correct implementation of allocators rather it stood as a starting point for me to learn on how best to implement functions like `malloc(size_t size)` `free(void *ptr)`
`realloc(void *ptr, size_t size)`

## FILES
`./src/main.c`
- This is a file where I play around with a char array which servers as a region for memory.

`./src/merge_blocks.c`
- This file is essentially the same as the one before but I was playing around with how to implement functions like `free(void *ptr)` to get a better understanding on certain logic like merging blocks


## Running the Program

To run the program, follow these steps:

1. Clone the repository:

   ```bash
   git clone <https://github.com/kam-stand/KH_MALLOC.git>
   ```

2. Change into the root directory:

   ```bash
   cd 'SIMPLE_MALLOC/arena_allocator'
   ```

3. Make the `run.sh` script executable:

   ```bash
   chmod +x run.sh
   ```

4. Run the script with the file you:
   ```bash
   /run.sh ./src/merge_blocks.c    
   ```
   or 
   ```bash
   /run.sh ./src/main.c    
   
## Useful links to help implement your own memory allocator
[write-a-simple-memory-allocator](https://arjunsreedharan.org/post/148675821737/memory-allocators-101-write-a-simple-memory)