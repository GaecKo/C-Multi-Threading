#!/bin/bash
# nproc: récup le nbre de coeur du CPU

# 1) Cleaning projet
make clean -s

# 2) Create exec files
make -s

# 5) Test on Reader - Writer
printf "= = = = = = = = = = = = = = = = = = = = = = =\n\nLaunching reader - writer tests...\n"

# | 5.1: file
lect_path="data/lect_writer.csv"

# | 5.2: first line of csv
echo "nb_thread, x1, x2, x3, x4, x5" > "$lect_path"

# | 5.3) testing with 1 to 64 threads 
for i in 2 4 8 16 32 64; do 
    line="$i"
    printf "Test with $i threads:\n"
    for j in {1..5}; do
        n_t=$(expr $i / 2)
        # Retrieve execution time
        exec_time=$(/usr/bin/time -f %e ./c/lect_writer $n_t $n_t 2>&1)
        echo "x$j: $exec_time"
        if [[ "$exec_time" == *"status"* ]]; then
            line="$line, ERROR"
        else
            line="$line, $exec_time"
        fi 
    done
    # Append the line to csv
    echo "$line" >> "$lect_path"
    printf "\n"
done

python3 analyser.py