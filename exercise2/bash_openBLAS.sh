#!/bin/bash

# Create a directory to store the results
day=$(date '+%Y-%m-%d')
time=$(date '+%T')
results_dir="results_openBLAS_${day}_${time}"
mkdir -p "$results_dir"

# Define the range of input values
start=2000
end=20000
step=1000

# Define the number of times to repeat the test (then we will do the average on the runs)
num_runs=3

# Double loop to do more tests (a test is a run), each test is formed by results coming from different inputs
for ((run = 1; run <= num_runs; run++)); do
    # Loop through inputs and run the C program
    for ((input = start; input <= end; input += step)); do
        output=$(./gemm_oblas.x "$input" "$input" "$input" | tail -n 1 | grep ";")
        echo "$output" >>"${results_dir}/${results_dir}_${run}.txt"
    done
done

