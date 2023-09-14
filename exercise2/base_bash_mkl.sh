#!/bin/bash

# Create a directory to store the results
results_dir="results_mkl"
mkdir -p "$results_dir"

# define the range of input values
start=2000
end=20000
step=8000

# Define the number of times to run the script
num_runs=2

# Loop for the specified number of runs
for ((run = 1; run <= num_runs; run++)); do
    # Loop through inputs and run the C program
    for ((input = start; input <= end; input += step)); do
        output=$(./gemm_mkl.x "$input" "$input" "$input" | tail -n 1 | grep ";")
        echo "$output" >>"${results_dir}/${results_dir}_${run}.txt"
    done
done



# TODO: use the command date to create a new folder to store new results. The name of the folder should contain the date (day) and the time