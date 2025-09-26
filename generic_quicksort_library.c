
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

#include "generic_quicksort_library.h"

#include <stdio.h>

const char *convert_error_num_to_error_string(int error_num)
{

    if (error_num == GQL_COMPARE_ELEMENTS_FUNCTION_PTR_IS_NULL) {
        return ("The function pointer given for comparing the elements is"
                " NULL.");
    } else if (error_num == GQL_SWAP_ELEMENTS_FUNCTION_PTR_IS_NULL) {
        return ("The function pointer given for swapping the elements is"
                " NULL.");
    }

    return ("Invalid error number given.");

} // end of function convert_error_num_to_error_string()

int generic_quicksort_ascending(void *array_ptr, int id,
                                long start_index, long end_index,
                                compare_elements_function_ptr comp_func,
                                swap_elements_function_ptr swap_func)
{

    long pivot_index = -1;
    long forward_ptr_index = start_index;
    long backward_ptr_index = end_index - 1;
    int retval = -1;

    if (!comp_func) {
        return GQL_COMPARE_ELEMENTS_FUNCTION_PTR_IS_NULL;
    }

    if (!swap_func) {
        return GQL_SWAP_ELEMENTS_FUNCTION_PTR_IS_NULL;
    }

    if ((start_index < 0) || (end_index < 0)) {
        return GQL_SUCCESS;
    }

    if (start_index >= end_index) {
        return GQL_SUCCESS;
    }

    if ((end_index - start_index) == 1) { // two elements
        if (comp_func(array_ptr, id, start_index, end_index) > 0) {
            swap_func(array_ptr, id, start_index, end_index);
        }
        return GQL_SUCCESS;
    }

    pivot_index = (start_index + end_index)/2;

    swap_func(array_ptr, id, pivot_index, end_index);

    while (1) {

        while (comp_func(array_ptr, id, forward_ptr_index, end_index) <= 0) {
            forward_ptr_index = forward_ptr_index + 1;
            if (forward_ptr_index == end_index) {
                break;
            }
        }

        while (comp_func(array_ptr, id, backward_ptr_index, end_index) >= 0) {
            backward_ptr_index = backward_ptr_index - 1;
            if (backward_ptr_index == (start_index - 1)) {
                break;
            }
        }

        if (forward_ptr_index < backward_ptr_index) {
            swap_func(array_ptr, id, forward_ptr_index, backward_ptr_index);
            forward_ptr_index = forward_ptr_index + 1;
            backward_ptr_index = backward_ptr_index - 1;
            continue;
        } else if (forward_ptr_index > backward_ptr_index) {
            // If forward_ptr_index is equal to the end_index then all the
            // elements from start_index till (end_index - 1) are smaller than
            // the element at the end_index.
            if (forward_ptr_index == end_index) {
                retval = generic_quicksort_ascending(array_ptr, id, start_index,
                                                     end_index - 1, comp_func,
                                                     swap_func);
                if (retval != GQL_SUCCESS) {
                    return retval;
                }
            } else { // forward_ptr_index is less than the end_index 
                swap_func(array_ptr, id, forward_ptr_index, end_index);
                retval = generic_quicksort_ascending(array_ptr, id, start_index,
                                                     forward_ptr_index - 1,
                                                     comp_func, swap_func);
                if (retval != GQL_SUCCESS) {
                    return retval;
                }
                retval = generic_quicksort_ascending(array_ptr, id,
                                                     forward_ptr_index + 1,
                                                     end_index, comp_func,
                                                     swap_func);
                if (retval != GQL_SUCCESS) {
                    return retval;
                }
            }
        } else {
            // At this point, forward_ptr_index is equal to the
            // backward_ptr_index. But this should not happen. This means that
            // there is/are some bug(s) in this library. So, we will print an
            // error message on 'stderr' and then crash this library so that the
            // program using this library also crashes and a core dump is
            // generated for debugging.
            fprintf(stderr, "There is/are some bug(s) in this library (%s)"
                    " because forward_ptr_index (%ld) is equal to the"
                    " backward_ptr_index (%ld) and this should not happen."
                    " Crashing this library so that the program using this"
                    " library also crashes and a core dump is generated for"
                    " debugging.\n", __FILE__, forward_ptr_index,
                    backward_ptr_index);

            // The following line of code will crash this library.
            (*((char *)(-1))) = 1;
        }
        
        return GQL_SUCCESS;

    } // end of while (1) loop

    // Code execution will not reach here.
    return GQL_SUCCESS;

} // end of function generic_quicksort_ascending()

int generic_quicksort_descending(void *array_ptr, int id,
                                 long start_index, long end_index,
                                 compare_elements_function_ptr comp_func,
                                 swap_elements_function_ptr swap_func)
{

    long pivot_index = -1;
    long forward_ptr_index = start_index;
    long backward_ptr_index = end_index - 1;
    int retval = -1;

    if (!comp_func) {
        return GQL_COMPARE_ELEMENTS_FUNCTION_PTR_IS_NULL;
    }

    if (!swap_func) {
        return GQL_SWAP_ELEMENTS_FUNCTION_PTR_IS_NULL;
    }

    if ((start_index < 0) || (end_index < 0)) {
        return GQL_SUCCESS;
    }

    if (start_index >= end_index) {
        return GQL_SUCCESS;
    }

    if ((end_index - start_index) == 1) { // two elements
        if (comp_func(array_ptr, id, start_index, end_index) < 0) {
            swap_func(array_ptr, id, start_index, end_index);
        }
        return GQL_SUCCESS;
    }

    pivot_index = (start_index + end_index)/2;

    swap_func(array_ptr, id, pivot_index, end_index);

    while (1) {

        while (comp_func(array_ptr, id, forward_ptr_index, end_index) >= 0) {
            forward_ptr_index = forward_ptr_index + 1;
            if (forward_ptr_index == end_index) {
                break;
            }
        }

        while (comp_func(array_ptr, id, backward_ptr_index, end_index) <= 0) {
            backward_ptr_index = backward_ptr_index - 1;
            if (backward_ptr_index == (start_index - 1)) {
                break;
            }
        }

        if (forward_ptr_index < backward_ptr_index) {
            swap_func(array_ptr, id, forward_ptr_index, backward_ptr_index);
            forward_ptr_index = forward_ptr_index + 1;
            backward_ptr_index = backward_ptr_index - 1;
            continue;
        } else if (forward_ptr_index > backward_ptr_index) {
            // If forward_ptr_index is equal to the end_index then all the
            // elements from start_index till (end_index - 1) are greater than
            // the element at the end_index.
            if (forward_ptr_index == end_index) {
                retval = generic_quicksort_descending(array_ptr, id,
                                                      start_index,
                                                      end_index - 1, comp_func,
                                                      swap_func);
                if (retval != GQL_SUCCESS) {
                    return retval;
                }
            } else { // forward_ptr_index is less than the end_index 
                swap_func(array_ptr, id, forward_ptr_index, end_index);
                retval = generic_quicksort_descending(array_ptr, id,
                                                      start_index,
                                                      forward_ptr_index - 1,
                                                      comp_func, swap_func);
                if (retval != GQL_SUCCESS) {
                    return retval;
                }
                retval = generic_quicksort_descending(array_ptr, id,
                                                      forward_ptr_index + 1,
                                                      end_index, comp_func,
                                                      swap_func);
                if (retval != GQL_SUCCESS) {
                    return retval;
                }
            }
        } else {
            // At this point, forward_ptr_index is equal to the
            // backward_ptr_index. But this should not happen. This means that
            // there is/are some bug(s) in this library. So, we will print an
            // error message on 'stderr' and then crash this library so that the
            // program using this library also crashes and a core dump is
            // generated for debugging.
            fprintf(stderr, "There is/are some bug(s) in this library (%s)"
                    " because forward_ptr_index (%ld) is equal to the"
                    " backward_ptr_index (%ld) and this should not happen."
                    " Crashing this library so that the program using this"
                    " library also crashes and a core dump is generated for"
                    " debugging.\n", __FILE__, forward_ptr_index,
                    backward_ptr_index);

            // The following line of code will crash this library.
            (*((char *)(-1))) = 1;
        }
        
        return GQL_SUCCESS;

    } // end of while (1) loop

    // Code execution will not reach here.
    return GQL_SUCCESS;

} // end of function generic_quicksort_descending()

