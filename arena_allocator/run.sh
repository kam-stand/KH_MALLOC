#!/bin/bash

src=$1
bin="./bin"
gcc -Wall -Wextra $src -o out
mv ./out $bin

${bin}/out