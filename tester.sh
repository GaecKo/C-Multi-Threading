#!/bin/bash
# nproc: récup le nbre de coeur du CPU

# 1) Cleaning projet
make clean -s

# 2) Create exec files
make -s

# 3) Test on philosophe
# | 3.1: file
phil_path="data/philosophe.csv"

# | 3.2: first line of csv
echo "nb_thread, x1, x2, x3, x4, x5" > "$phil_path"

# | 3.3) testing with 1 to 64 threads 
for i in 2 4 8 16 32 64; do 
    line="$i"
    echo "Test with $i threads:"
    for j in {1..5}; do
        # Retrieve execution time
        exec_time=$(/usr/bin/time -f %e ./c/philosophe $i 2>&1)
        echo "x$j: $exec_time"
        line="$line, $exec_time"
    done
    # Append the line to csv
    echo "$line" >> "$phil_path"
done
