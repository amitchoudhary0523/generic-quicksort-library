
/*
 * License:
 *
 * This file has been released under "unlicense" license
 * (https://unlicense.org).
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or distribute
 * this software, either in source code form or as a compiled binary, for any
 * purpose, commercial or non-commercial, and by any means.
 *
 * For more information about this license, please visit - https://unlicense.org
 */

/*
 * Author: Amit Choudhary
 * Email: amitchoudhary0523 AT gmail DOT com
 */

#ifndef _GENERIC_QUICKSORT_LIBRARY_H_
#define _GENERIC_QUICKSORT_LIBRARY_H_


// GQL/gql means generic quicksort library.


// Success and error macros are defined below.

// Everything happened successfully.
#define GQL_SUCCESS 0

// The function pointer given by the user for comparing the elements is NULL.
#define GQL_COMPARE_ELEMENTS_FUNCTION_PTR_IS_NULL -1

// The function pointer given by the user for swapping the elements is NULL.
#define GQL_SWAP_ELEMENTS_FUNCTION_PTR_IS_NULL -2

// This value is used only for initializing error variables.
#define GQL_ERROR_INIT_VALUE -100


/*
 * The user needs to give the function pointer of a function that will compare
 * the elements of the array.
 *
 * This function will get four arguments - 'array_ptr', 'id, 'first_index' and
 * 'second_index'. The 'first_index' and the 'second_index' will be the indices
 * of the array.
 *
 * The return value of this function should be a negative integer if the element
 * at the 'first_index' is less than the element at the 'second_index', 0 (zero)
 * if the element at the 'first_index' is equal to the element at the
 * 'second_index', and a positive integer if the element at the 'first_index' is
 * greater than the element at the 'second_index'.
 *
 * If the elements of 'array_ptr' are strings (char *), then the user should
 * handle NULL values and empty strings also.
 *
 * If the elements of 'array_ptr' are pointers (but not strings), then the user
 * should handle NULL values also.
 */
typedef int (*compare_elements_function_ptr)(void *array_ptr, int id,
                                             long first_index,
                                             long second_index);

/*
 * The user needs to give the function pointer of a function that will swap the
 * elements of the array.
 *
 * This function will get four arguments - 'array_ptr', 'id, 'first_index' and
 * 'second_index'. The 'first_index' and the 'second_index' will be the indices
 * of the array.
 *
 * The user has to swap the elements at 'first_index' and 'second_index'.
 */
typedef void (*swap_elements_function_ptr)(void *array_ptr, int id,
                                          long first_index,
                                          long second_index);

const char *convert_error_num_to_error_string(int error_num);

/*
 * generic_quicksort_ascending():
 *
 * The function generic_quicksort_ascending() will sort an array in ascending
 * order and the data type of the elements of the array can be anything, like -
 * int, long, char *, struct key_value *, etc. So, this function is independent
 * of the data type of the elements of the array and this function achieves this
 * by taking the function pointers for comparing the elements of the array and
 * for swapping the elements of the array from the "caller of this function".
 *
 * Arguments:
 *
 *      array_ptr: This is the pointer to the array that the user wants to sort.
 *                 This function will send 'array_ptr' back as an argument to
 *                 the compare elements function and to the swap elements
 *                 function so that the user doesn't have to make the array
 *                 global for accessing it in the compare elements / swap
 *                 elements functions.
 *
 *      id:        This argument 'id' is necessary if the user has only one
 *                 compare elements function and only one swap elements function
 *                 and the user wants to sort more than one array and the data
 *                 types of the elements of these arrays are different - for
 *                 example - one array has integer elements, another array has
 *                 string elements, etc. So, in these two functions, the user
 *                 will have to know the data type of the elements of
 *                 'array_ptr' so that the user can do the right thing. So, for
 *                 this, 'id' is required. The user will send the 'id' as an
 *                 argument to this function and this function will send this
 *                 'id' back to the compare elements / swap elements functions
 *                 so that the user can identify the data type of the elements
 *                 of 'array_ptr' and do the right thing. So, the user can send
 *                 the 'id' as 1 for integer data type, 2 for long, 3 for
 *                 string, 4 for a user defined structure, etc.
 *
 *      start_index: This is the index of 'array_ptr' from where the user wants
 *                   to start sorting the array. In general, this will be
 *                   0 (zero).
 *
 *      end_index: This is the index of 'array_ptr' till which the user wants to
 *                 sort the array. In general, this will be the last index of
 *                 'array_ptr' (number_of_elements_in_array_ptr - 1).
 *
 *      comp_func: This is the function pointer of the function that will
 *                 compare the elements of 'array_ptr'.
 *
 *                 This function will get four arguments - 'array_ptr', 'id,
 *                 'first_index' and 'second_index'. The 'first_index' and the
 *                 'second_index' will be the indices of 'array_ptr'.
 *
 *                 The return value of this function should be a negative
 *                 integer if the element at the 'first_index' is less than the
 *                 element at the 'second_index', 0 (zero) if the element at the
 *                 'first_index' is equal to the element at the 'second_index',
 *                 and a positive integer if the element at the 'first_index' is
 *                 greater than the element at the 'second_index'.
 *
 *      swap_func: This is the function pointer of the function that will
 *                 swap the elements of 'array_ptr'.
 *
 *                 This function will get four arguments - 'array_ptr', 'id,
 *                 'first_index' and 'second_index'. The 'first_index' and the
 *                 'second_index' will be the indices of 'array_ptr'.
 *
 *                 The user has to swap the elements at 'first_index' and
 *                 'second_index'.
 */
int generic_quicksort_ascending(void *array_ptr, int id,
                                long start_index, long end_index,
                                compare_elements_function_ptr comp_func,
                                swap_elements_function_ptr swap_func);
/*
 * generic_quicksort_descending():
 *
 * The function generic_quicksort_descending() will sort an array in descending
 * order.
 *
 * The rest of the details for this function are the same as for the function
 * generic_quicksort_ascending(). Please look above for the details of the
 * function generic_quicksort_ascending().
 */
 
int generic_quicksort_descending(void *array_ptr, int id,
                                 long start_index, long end_index,
                                 compare_elements_function_ptr comp_func,
                                 swap_elements_function_ptr swap_func);
#endif

