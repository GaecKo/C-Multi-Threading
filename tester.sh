#!/bin/bash
# nproc: récup le nbre de coeur du CPU

# 1) making sure project is clear
make clean &> /dev/null

# 2) testing with 1 to 8 threads
for i in {1..8} 
do
    echo "Test with $i threads"
    start=`date +%s`
    make -j $i -s &> /dev/null
    end=`date +%s`
    echo Execution time was `expr $end - $start` seconds.
    make clean &> /dev/null
done



# ==== OR? ====



#!/bin/bash
# nproc: récup le nbre de coeur du CPU

# 1) making sure project is clear
make clean -s

# 2) testing with 1 to 8 threads
for i in {1..8} 
do
    echo "Test with $i threads"

    /usr/bin/time -f %e make -s -j $i 

    make clean -s
done

