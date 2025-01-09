test="./src/test.c"
library="../src/mem_lib.c"
bin="./bin"
gcc -Wall -Wextra $test $library -o out
mv ./out $bin

${bin}/out