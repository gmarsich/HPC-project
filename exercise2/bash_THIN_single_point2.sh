#!/bin/bash

# Create a directory to store the results
day=$(date '+%Y-%m-%d')
time=$(date '+%T')
results_dir="results_THIN_pt2_single_${day}_${time}"
mkdir -p "$results_dir"

# Size of the matrix
input=12000

# Max number of cores
n_cores=12

# Define the number of times to repeat the test (then we will do the average on the runs)
num_runs=7

# Double loop to do more tests (a test is a run), each test is formed by results coming from a different amount of cores
for ((run = 1; run <= num_runs; run++)); do
    # Loop through inputs and run the C program
    for ((i=1; i <= n_cores; i++)); do
        output_mkl=$(srun -n1 --cpus-per-task=$i ./gemm_mkl.x "$input" "$input" "$input" | tail -n 1 | grep ",")
        echo "$i,$output_mkl" >>"${results_dir}/${results_dir}_mkl_${run}.csv"
        output_openBLAS=$(srun -n1 --cpus-per-task=$i ./gemm_oblas.x "$input" "$input" "$input" | tail -n 1 | grep ",")
        echo "$i,$output_openBLAS" >>"${results_dir}/${results_dir}_openBLAS_${run}.csv"
        output_BLIS=$(srun -n1 --cpus-per-task=$i ./gemm_blis.x "$input" "$input" "$input" | tail -n 1 | grep ",")
        echo "$i,$output_BLIS" >>"${results_dir}/${results_dir}_BLIS_${run}.csv"
    done
done