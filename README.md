
File "generic_quicksort_library.c" implements two generic quicksort functions.
These functions are - generic_quicksort_ascending() and
generic_quicksort_descending().

generic_quicksort_ascending() sorts an array in ascending order and
generic_quicksort_descending() sorts an array in descending order.

These functions can sort an array having any data type - int, long, char *,
struct key_value *, etc. These functions achieve this by taking the function
pointers for comparing the elements of the array and for swapping the elements
of the array from the "caller of these functions". Because of this, the two
functions of the generic quicksort library don't need to know what is the data
type of the elements of the array.

File "test_generic_quicksort_library.c" implements code to test the
generic_quicksort_ascending() and generic_quicksort_descending() functions.

There is also a bash shell script (run_test_generic_quicksort_library.sh) for
running the program (test_generic_quicksort_library.out) endlessly in a loop but
you probably don't need this.

---- End of README ----
