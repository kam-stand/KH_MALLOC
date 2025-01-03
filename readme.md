# KH_MALLOC

KH_MALLOC is a simple implementation of memory management functions in C, such as `malloc` and `free`. This library uses `sbrk()` to initialize memory on the heap.

# HEADER_FILES

The header files contain the function declarations for the memory management functions provided by the KH_MALLOC library. Include these headers in your C programs to use the custom `malloc` and `free` implementations.
## NOTE
As of right now the following functions are not implemented
```c
kh_free(void *ptr) // Takes in a pointer to free memory
kh_realloc(void *ptr) // Takes in a pointer to adjust the memory size 
```
```c
#include "kh_malloc.h"
```

## How to Run

To run the program, use the provided bash script `run.sh`. This script will compile the code and execute the program.

```bash
./run.sh
```

Make sure you have execution permissions for the script. You can set the permissions using:

```bash
chmod +x run.sh
```

After setting the permissions, you can run the script to see the memory management functions in action.
