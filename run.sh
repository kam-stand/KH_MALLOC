#!/bin/bash
clear
main="./src/main.c"
library="./src/mem_lib.c"
bin="./bin"
gcc -Wall -Wextra $main $library -o out
mv ./out $bin

${bin}/out