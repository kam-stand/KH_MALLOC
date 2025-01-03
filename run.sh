#!/bin/bash

# Compile the main.c and queue.c files
gcc -o main main.c mem_lib.c

# Check if compilation was successful
if [ $? -eq 0 ]; then
    # Run the compiled program
    mv ./main ./build
    ./build/main
else
    echo "Compilation failed."
fi

