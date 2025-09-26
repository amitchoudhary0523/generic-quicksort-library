
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
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_ARRAY_ELEMENTS 100L
#define MAX_INT_VALUE_ALLOWED 10000

#define TRUE 1
#define FALSE 2

#define ASC 3 // ascending order
#define DESC 4 // descending order

#define INTEGER 5
#define STRING 6

#define MAX_STR_SIZE 3 // including null terminating character

#define ARRAY_IS_NOT_SORTED -1000

// Function prototypes for gcc flag -Werror-implicit-function-declaration.
int compare_elements(void *array_ptr, int id, long first_index,
                     long second_index);
void swap_elements(void *array_ptr, int id, long first_index,
                   long second_index);
void discard_all_characters_from_stdin(void);
void wait_for_user_to_press_enter(void);
int get_wait_for_user_option_value(int argc, char *argv[]);
char *get_random_alphabetical_string(int len);
void free_strings_of_array(char **array_ptr);
int test_if_array_is_sorted(void *array_ptr, int id, int sorting_order);
void print_array(void *array_ptr, int id);
void sort_array_of_integers(int sorting_order);
void sort_array_of_strings(int sorting_order);

// Read and discard all characters from stdin until '\n' or EOF is received.
void discard_all_characters_from_stdin(void)
{

    int c = 0;

    // discard all characters from stdin
    while ((c = getchar()) && (c != '\n') && (c != EOF));

    return;

} // end of function discard_all_characters_from_stdin()

void wait_for_user_to_press_enter(void)
{

    printf("Please press \"ENTER\" key to continue..");

    discard_all_characters_from_stdin();

    return;

} // end of function wait_for_user_to_press_enter()

int compare_elements(void *array_ptr, int id, long first_index,
                     long second_index)
{

    if (!array_ptr) {
        printf("\nError: %s(): Argument 'array_ptr' is NULL. Some bug(s) in"
               " generic quicksort library. Exiting..\n", __FUNCTION__);
        exit(EXIT_FAILURE);
    }

    if ((first_index < 0) || (first_index >= NUM_ARRAY_ELEMENTS)) {
        printf("\nError: %s(): Argument 'first_index' (%ld) is out of bounds"
               " (0 - %ld). Some bug(s) in generic quicksort library."
               " Exiting..\n", __FUNCTION__, first_index, NUM_ARRAY_ELEMENTS);
        exit(EXIT_FAILURE);
    }

    if ((second_index < 0) || (second_index >= NUM_ARRAY_ELEMENTS)) {
        printf("\nError: %s(): Argument 'second_index' (%ld) is out of bounds"
               " (0 - %ld). Some bug(s) in generic quicksort library."
               " Exiting..\n", __FUNCTION__, second_index, NUM_ARRAY_ELEMENTS);
        exit(EXIT_FAILURE);
    }

    if (id == INTEGER) {
        int *arr_ptr = (int *)(array_ptr);
        if (arr_ptr[first_index] > arr_ptr[second_index]) {
            return 1;
        } else if (arr_ptr[first_index] < arr_ptr[second_index]) {
            return -1;
        } else {
            return 0;
        }
    } else if (id == STRING) {
        char **arr_ptr = (char **)(array_ptr);
        char *first_string = arr_ptr[first_index]; 
        char *second_string = arr_ptr[second_index]; 
        if ((first_string == NULL) && (second_string == NULL)) {
            return 0;
        } else if (first_string == NULL) {
            return -1;
        } else if (second_string == NULL) {
            return 1;
        }
        return (strncmp(first_string, second_string, MAX_STR_SIZE));
    }

    // Got invalid 'id'.
    printf("\nError: %s(): Argument 'id' (%d) is invalid. Some bug(s) in"
           " generic quicksort library. Exiting..\n", __FUNCTION__, id);
    exit(EXIT_FAILURE);

} // end of function compare_elements()

void swap_elements(void *array_ptr, int id, long first_index, long second_index)
{

    if (!array_ptr) {
        printf("\nError: %s(): Argument 'array_ptr' is NULL. Some bug(s) in"
               " generic quicksort library. Exiting..\n", __FUNCTION__);
        exit(EXIT_FAILURE);
    }

    if ((first_index < 0) || (first_index >= NUM_ARRAY_ELEMENTS)) {
        printf("\nError: %s(): Argument 'first_index' (%ld) is out of bounds"
               " (0 - %ld). Some bug(s) in generic quicksort library."
               " Exiting..\n", __FUNCTION__, first_index, NUM_ARRAY_ELEMENTS);
        exit(EXIT_FAILURE);
    }

    if ((second_index < 0) || (second_index >= NUM_ARRAY_ELEMENTS)) {
        printf("\nError: %s(): Argument 'second_index' (%ld) is out of bounds"
               " (0 - %ld). Some bug(s) in generic quicksort library."
               " Exiting..\n", __FUNCTION__, second_index, NUM_ARRAY_ELEMENTS);
        exit(EXIT_FAILURE);
    }

    if (id == INTEGER) {
        int *arr_ptr = (int *)(array_ptr);
        int temp = arr_ptr[first_index];
        arr_ptr[first_index] = arr_ptr[second_index];
        arr_ptr[second_index] = temp;
        return;
    } else if (id == STRING) {
        char **arr_ptr = (char **)(array_ptr);
        char *temp = arr_ptr[first_index];
        arr_ptr[first_index] = arr_ptr[second_index];
        arr_ptr[second_index] = temp;
        return;
    }

    // Got invalid 'id'.
    printf("\nError: %s(): Argument 'id' (%d) is invalid. Some bug(s) in"
           " generic quicksort library. Exiting..\n", __FUNCTION__, id);
    exit(EXIT_FAILURE);

} // end of function swap_elements()

int test_if_array_is_sorted(void *array_ptr, int id, int sorting_order)
{

    long i = 0;
    long last_index = NUM_ARRAY_ELEMENTS - 1;

    if (!array_ptr) {
        printf("\nError: %s(): Argument 'array_ptr' is NULL. Exiting..\n",
               __FUNCTION__);
        exit(EXIT_FAILURE);
    }

    if ((sorting_order != ASC) && (sorting_order != DESC)) {
        printf("\nError: %s(): Argument 'sorting_order' (%d) is neither"
               " ascending (%d) nor descending (%d). Exiting..\n", __FUNCTION__,
               sorting_order, ASC, DESC);
        exit(EXIT_FAILURE);
    }

    if (id == INTEGER) {

        int *arr_ptr = (int *)(array_ptr);

        if (sorting_order == ASC) {
            for (i = 0; i < last_index; i++) {
                if (arr_ptr[i] > arr_ptr[i + 1]) {
                    return ARRAY_IS_NOT_SORTED;
                }
            } // end of for loop
            return GQL_SUCCESS;
        } else { // descending order
            for (i = 0; i < last_index; i++) {
                if (arr_ptr[i] < arr_ptr[i + 1]) {
                    return ARRAY_IS_NOT_SORTED;
                }
            } // end of for loop
            return GQL_SUCCESS;
        }

    } else if (id == STRING) {

        char **arr_ptr = (char **)(array_ptr);

        if (sorting_order == ASC) {
            for (i = 0; i < last_index; i++) {
                if (strncmp((arr_ptr[i] ? arr_ptr[i] : ""),
                            (arr_ptr[i+1] ? arr_ptr[i+1] : ""),
                            MAX_STR_SIZE) > 0) {
                    return ARRAY_IS_NOT_SORTED;
                }
            } // end of for loop
            return GQL_SUCCESS;
        } else { // descending order
            for (i = 0; i < last_index; i++) {
                if (strncmp((arr_ptr[i] ? arr_ptr[i] : ""),
                            (arr_ptr[i+1] ? arr_ptr[i+1] : ""),
                            MAX_STR_SIZE) < 0) {
                    return ARRAY_IS_NOT_SORTED;
                }
            } // end of for loop
            return GQL_SUCCESS;
        }

    } // end of if-else id == INTEGER or STRING

    // Got invalid 'id'.
    printf("\nError: %s(): Argument 'id' (%d) is invalid. Some bug(s) in"
           " generic quicksort library. Exiting..\n", __FUNCTION__, id);
    exit(EXIT_FAILURE);

} // end of function test_if_array_is_sorted()

void print_array(void *array_ptr, int id)
{

    long i = 0;

    if (!array_ptr) {
        printf("\nError: %s(): Argument 'array_ptr' is NULL. Exiting..\n",
               __FUNCTION__);
        exit(EXIT_FAILURE);
    }

    if (id == INTEGER) {
        int *arr_ptr = (int *)(array_ptr);
        printf("\n");
        for (i = 0; i < NUM_ARRAY_ELEMENTS; i++) {
            printf("%d%s", arr_ptr[i],
            ((i != (NUM_ARRAY_ELEMENTS -1)) ? ", " : "."));
        }
        printf("\n");
        return;
    } else if (id == STRING) {
        char **arr_ptr = (char **)(array_ptr);
        printf("\n");
        for (i = 0; i < NUM_ARRAY_ELEMENTS; i++) {
            printf("%s%s", arr_ptr[i],
            ((i != (NUM_ARRAY_ELEMENTS -1)) ? ", " : "."));
        }
        printf("\n");
        return;
    }

    // Got invalid 'id'.
    printf("\nError: %s(): Argument 'id' (%d) is invalid. Some bug(s) in"
           " generic quicksort library. Exiting..\n", __FUNCTION__, id);
    exit(EXIT_FAILURE);

} // end of function print_array()

void sort_array_of_integers(int sorting_order)
{

    int arr[NUM_ARRAY_ELEMENTS];
    int retval = GQL_ERROR_INIT_VALUE;
    char *asc = "ascending";
    char *desc = "descending";
    long i = 0;

    if ((sorting_order != ASC) && (sorting_order != DESC)) {
        printf("\nError: %s(): Argument 'sorting_order' (%d) is neither"
               " ascending (%d) nor descending (%d). Exiting..\n", __FUNCTION__,
               sorting_order, ASC, DESC);
        exit(EXIT_FAILURE);
    }

    srand((unsigned int)(time(NULL)));

    for (i = 0; i < NUM_ARRAY_ELEMENTS; i++) {
        arr[i] = rand() % (MAX_INT_VALUE_ALLOWED + 1);
    }

    printf("\n");
    printf("===================================================\n");
    printf("Sorting an array of integers in \"%s\" order.\n",
           ((sorting_order == ASC) ? asc : desc));
    printf("===================================================\n");

    if (sorting_order == ASC) {
        retval = generic_quicksort_ascending(arr, INTEGER, 0,
                                             NUM_ARRAY_ELEMENTS - 1,
                                             compare_elements, swap_elements);
    } else { // descending order
        retval = generic_quicksort_descending(arr, INTEGER, 0,
                                              NUM_ARRAY_ELEMENTS - 1,
                                              compare_elements, swap_elements);
    }

    if (retval != GQL_SUCCESS) {
        printf("\nError: %s(): [Error number: %d]. The array of integers was"
               " not sorted successfully. Some bug(s) in generic quicksort"
               " library. Exiting..\n", __FUNCTION__, retval);
        exit(EXIT_FAILURE);
    }

    retval = test_if_array_is_sorted(arr, INTEGER, sorting_order);

    if (retval != GQL_SUCCESS) {
        printf("\nError: %s(): [Error number: %d]. The array of integers was"
               " not sorted successfully. Some bug(s) in generic quicksort"
               " library. Exiting..\n", __FUNCTION__, retval);
        exit(EXIT_FAILURE);
    }

    printf("\nThe array of integers was sorted successfully in \"%s\" order.\n",
           ((sorting_order == ASC) ? asc : desc));

    printf("\nPrinting the sorted array of integers:\n");

    print_array(arr, INTEGER);

    printf("\n");

    return;

} // end of function sort_array_of_integers()

char *get_random_alphabetical_string(int len)
{

    char *str = NULL;
    int i = 0;

    if ((len < 0) || (len > (MAX_STR_SIZE - 1))) {
        return NULL;
    }

    str = calloc((size_t)(len+1), 1); // extra 1 for null terminating character 

    if (!str) {
        printf("\nError: %s(): No memory available. Exiting..\n", __FUNCTION__);
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < len; i++) {
        str[i] = (char)('a' + (rand() % 26));
    }

    str[i] = 0;

    return str;

} // end of function get_random_alphabetical_string()

void free_strings_of_array(char **array_ptr)
{

    long i = 0;

    if (!array_ptr) {
        return;
    }

    for (i = 0; i < NUM_ARRAY_ELEMENTS; i++) {
        free(array_ptr[i]);
        array_ptr[i] = NULL;
    }

    return;

} // end of function free_strings_of_array()

void sort_array_of_strings(int sorting_order)
{

    char *arr[NUM_ARRAY_ELEMENTS];
    int retval = GQL_ERROR_INIT_VALUE;
    char *asc = "ascending";
    char *desc = "descending";
    long i = 0;

    if ((sorting_order != ASC) && (sorting_order != DESC)) {
        printf("\nError: %s(): Argument 'sorting_order' (%d) is neither"
               " ascending (%d) nor descending (%d). Exiting..\n", __FUNCTION__,
               sorting_order, ASC, DESC);
        exit(EXIT_FAILURE);
    }

    srand((unsigned int)(time(NULL)));

    for (i = 0; i < NUM_ARRAY_ELEMENTS; i++) {
        if ((i % 40) == 0) {
            arr[i] = get_random_alphabetical_string(0);
        } else if ((i % 20) == 0) {
            arr[i] = get_random_alphabetical_string(MAX_STR_SIZE * 2);
        } else {
            arr[i] = get_random_alphabetical_string(MAX_STR_SIZE - 1);
        }
    } // end of for loop

    printf("\n");
    printf("==================================================\n");
    printf("Sorting an array of strings in \"%s\" order.\n",
           ((sorting_order == ASC) ? asc : desc));
    printf("==================================================\n");

    if (sorting_order == ASC) {
        retval = generic_quicksort_ascending(arr, STRING, 0,
                                             NUM_ARRAY_ELEMENTS - 1,
                                             compare_elements, swap_elements);
    } else { // descending order
        retval = generic_quicksort_descending(arr, STRING, 0,
                                              NUM_ARRAY_ELEMENTS - 1,
                                              compare_elements, swap_elements);
    }

    if (retval != GQL_SUCCESS) {
        printf("\nError: %s(): [Error number: %d]. The array of strings was"
               " not sorted successfully. Some bug(s) in generic quicksort"
               " library. Exiting..\n", __FUNCTION__, retval);
        exit(EXIT_FAILURE);
    }

    retval = test_if_array_is_sorted(arr, STRING, sorting_order);

    if (retval != GQL_SUCCESS) {
        printf("\nError: %s(): [Error number: %d]. The array of strings was"
               " not sorted successfully. Some bug(s) in generic quicksort"
               " library. Exiting..\n", __FUNCTION__, retval);
        exit(EXIT_FAILURE);
    }

    printf("\nThe array of strings was sorted successfully in \"%s\" order.\n",
           ((sorting_order == ASC) ? asc : desc));

    printf("\nPrinting the sorted array of strings:\n");

    print_array(arr, STRING);

    printf("\n");

    free_strings_of_array(arr);

    return;

} // end of function sort_array_of_strings()

int get_wait_for_user_option_value(int argc, char *argv[])
{

    int wait_for_user = TRUE;

    if ((argc >= 2) && (strcmp(argv[1], "--no-wait") == 0)) {
        wait_for_user = FALSE;
    }

    return wait_for_user;

} // end of function get_wait_for_user_option_value()

int main(int argc, char *argv[])
{

    int wait_for_user = TRUE;

    wait_for_user = get_wait_for_user_option_value(argc, argv);

    // sort array of integers in ascending order
    sort_array_of_integers(ASC);

    if (wait_for_user == TRUE) {
        wait_for_user_to_press_enter();
    }

    // sort array of strings in ascending order
    sort_array_of_strings(ASC);

    if (wait_for_user == TRUE) {
        wait_for_user_to_press_enter();
    }

    // sort array of integers in descending order
    sort_array_of_integers(DESC);

    if (wait_for_user == TRUE) {
        wait_for_user_to_press_enter();
    }

    // sort array of strings in descending order
    sort_array_of_strings(DESC);

    exit(EXIT_SUCCESS);

} // end of function main()

