#!/bin/bash
# nproc: retrieves the number of CPU cores

# 1) 1 arg exec call
perform_test_one_arg() {
    local executable="$1"
    local path="$2"

    echo "nb_thread, x1, x2, x3, x4, x5" > "$path"

    for i in 2 4 8 16 32 64; do
        line="$i"
        printf "Test with $i threads:\n"
        for j in {1..5}; do
            exec_time=$(/usr/bin/time -f %e "./executables/$executable" "$i" 2>&1)
            echo "x$j: $exec_time"
            if [[ "$exec_time" == *"status"* ]]; then
                line="$line, ERROR"
            else
                line="$line, $exec_time"
            fi
        done
        echo "$line" >> "$path"
        printf "\n"
    done
}

# 2) 2 args exec call
perform_test_two_args() {
    local executable="$1"
    local path="$2"

    echo "nb_thread, x1, x2, x3, x4, x5" > "$path"

    for i in 2 4 8 16 32 64; do
        line="$i"
        printf "Test with $i threads:\n"
        for j in {1..5}; do
            n_t=$(expr $i / 2)
            exec_time=$(/usr/bin/time -f %e "./executables/$executable" "$n_t" "$n_t" 2>&1)
            echo "x$j: $exec_time"
            if [[ "$exec_time" == *"status"* ]]; then
                line="$line, ERROR"
            else
                line="$line, $exec_time"
            fi
        done
        echo "$line" >> "$path"
        printf "\n"
    done
}

# 3) ############ Test on philosopher ############
printf "Launching problem of philosopher test...\n\n"


perform_test_one_arg "philosophe" "data/philosophe.csv"

#                       -----
printf "Launching problem of philosopher test with our sem...\n\n"

perform_test_one_arg "philosophe2" "data/philosophe2.csv"

# 4) ############ Test on Prod-Conso ############
printf "= = = = = = = = = = = = = = = = = = = = = = =\n\nLaunching Prod-Conso tests...\n"

perform_test_two_args "prod_conso" "data/prod_conso.csv"

#                       -----
printf "= = = = = = = = = = = = = = = = = = = = = = =\n\nLaunching Prod-Conso tests with our sem...\n"


perform_test_two_args "prod_conso2" "data/prod_conso2.csv"

# 5) ############ Test on Reader - Writer ############
printf "= = = = = = = = = = = = = = = = = = = = = = =\n\nLaunching reader - writer tests...\n"

perform_test_two_args "lect_writer" "data/lect_writer.csv"

#                       -----
printf "= = = = = = = = = = = = = = = = = = = = = = =\n\nLaunching reader - writer tests with our sem...\n"

perform_test_two_args "lect_writer2" "data/lect_writer2.csv"

# 6) ############ Test on 2.1 ############
printf "= = = = = = = = = = = = = = = = = = = = = = =\n\nLaunching test-and-set tests...\n"

perform_test_one_arg "test_and_set" "data/test_and_set.csv"

# 7) ############ Test on 2.3 ############
printf "= = = = = = = = = = = = = = = = = = = = = = =\n\nLaunching test-and-test-and-set tests...\n"

# Test with one argument
perform_test_one_arg "test_and_test_and_set" "data/test_and_test_and_set.csv"

printf "= = = = = = = = = = = = = = = = = = = = = = =\n\nTests done successfully!"

echo "### philo"
cat "data/philosophe.csv"
echo ""
echo "### philo2"
cat "data/philosophe2.csv"
echo""
echo "------------------------------"
echo""

echo "### lect"
cat "data/lect_writer.csv"
echo ""
echo "### lect2"
cat "data/lect_writer2.csv"
echo""
echo "------------------------------"
echo""

echo "### prod_conso"
cat "data/prod_conso.csv"
echo ""
echo "### prod_conso2"
cat "data/prod_conso2.csv"
echo""
echo "------------------------------"
echo""

echo "### test and set"
cat "data/test_and_set.csv"
echo ""
echo "### test and test and set"
cat "data/test_and_test_and_set.csv"
echo""
echo "------------------------------"
echo""