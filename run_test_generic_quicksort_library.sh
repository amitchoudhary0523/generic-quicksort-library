#!/bin/bash

count=0
retval=1

while true
do
    count=$((count+1)) 
    ./test_generic_quicksort_library.out --no-wait
    retval=$?
    echo
    set -x
    if [ "$retval" -ne "0" ]; then
        echo
        echo "test_generic_quicksort_library.out returned error."
        echo
        exit;
    fi
    set +x
    echo
    echo "---- `date \"+%Y-%m-%d-%H-%M-%S\"`, count = $count ----"
    echo
    sleep 1
done

