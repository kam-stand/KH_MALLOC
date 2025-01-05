

main_file='./main.c'
driver_fils='./include/kh_malloc.c'

gcc -o main $main_file $driver_fils

mv ./main ./build

./build/main
