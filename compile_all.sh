#!/bin/bash

set -x

rm -f generic_quicksort_library.o

rm -f test_generic_quicksort_library.out

gcc -c -Wall -Werror -Wextra -Wundef -Wunreachable-code -Winit-self -Wparentheses -Wconversion -Wsign-conversion -Wsign-compare -Werror-implicit-function-declaration -Wmissing-prototypes -Wmissing-declarations -Wformat-security generic_quicksort_library.c -o generic_quicksort_library.o

if [ "$?" -ne "0" ]; then
    exit;
fi

rm -f generic_quicksort_library.o

gcc -Wall -Werror -Wextra -Wundef -Wunreachable-code -Winit-self -Wparentheses -Wconversion -Wsign-conversion -Wsign-compare -Werror-implicit-function-declaration -Wmissing-prototypes -Wmissing-declarations -Wformat-security generic_quicksort_library.c test_generic_quicksort_library.c -o test_generic_quicksort_library.out

