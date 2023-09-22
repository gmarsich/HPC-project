import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from function_mean_matrix import mean_matrix

matrix_single_spread_MKL = mean_matrix('/home/gaia/Documents/RESULTS/RESULTS_fixed_size/spread/single/MKL')
matrix_single_spread_openBLAS = mean_matrix('/home/gaia/Documents/RESULTS/RESULTS_fixed_size/spread/single/OpenBLAS')
matrix_single_spread_BLIS = mean_matrix('/home/gaia/Documents/RESULTS/RESULTS_fixed_size/spread/single/BLIS')

matrix_single_close_MKL = mean_matrix('/home/gaia/Documents/RESULTS/RESULTS_fixed_size/close/single/MKL')
matrix_single_close_openBLAS = mean_matrix('/home/gaia/Documents/RESULTS/RESULTS_fixed_size/close/single/OpenBLAS')
matrix_single_close_BLIS = mean_matrix('/home/gaia/Documents/RESULTS/RESULTS_fixed_size/close/single/BLIS')


matrix_double_spread_MKL = mean_matrix('/home/gaia/Documents/RESULTS/RESULTS_fixed_size/spread/double/MKL')
matrix_double_spread_openBLAS = mean_matrix('/home/gaia/Documents/RESULTS/RESULTS_fixed_size/spread/double/OpenBLAS')
matrix_double_spread_BLIS = mean_matrix('/home/gaia/Documents/RESULTS/RESULTS_fixed_size/spread/double/BLIS')

matrix_double_close_MKL = mean_matrix('/home/gaia/Documents/RESULTS/RESULTS_fixed_size/close/double/MKL')
matrix_double_close_openBLAS = mean_matrix('/home/gaia/Documents/RESULTS/RESULTS_fixed_size/close/double/OpenBLAS')
matrix_double_close_BLIS = mean_matrix('/home/gaia/Documents/RESULTS/RESULTS_fixed_size/close/double/BLIS')


# Plot of elapsed time
plt.plot(matrix_single_spread_MKL[:, 0], matrix_single_spread_MKL[:, 4], label='spread, MKL', color='blue', marker='o')
plt.plot(matrix_single_spread_openBLAS[:, 0], matrix_single_spread_openBLAS[:, 4], label='spread, OpenBLAS', color='red', marker='x')
plt.plot(matrix_single_spread_BLIS[:, 0], matrix_single_spread_BLIS[:, 4], label='spread, BLIS', color='green', marker='2', markersize=10)
plt.plot(matrix_single_close_MKL[:, 0], matrix_single_close_MKL[:, 4], label='close, MKL', color='pink', marker='D')
plt.plot(matrix_single_close_openBLAS[:, 0], matrix_single_close_openBLAS[:, 4], label='close, OpenBLAS', color='black', marker='*', markersize=7)
plt.plot(matrix_single_close_BLIS[:, 0], matrix_single_close_BLIS[:, 4], label='close, BLIS', color='purple', marker='s')
plt.legend(loc='upper right')
plt.grid(True, linestyle='--', color='gray')
plt.xlabel('Number of available cores')
plt.ylabel('Elapsed time (seconds)')
plt.title("GEMM calculation with increasing number of available cores (THIN node, single precision)")
plt.show()

plt.plot(matrix_double_spread_MKL[:, 0], matrix_double_spread_MKL[:, 4], label='spread, MKL', color='blue', marker='o')
plt.plot(matrix_double_spread_openBLAS[:, 0], matrix_double_spread_openBLAS[:, 4], label='spread, OpenBLAS', color='red', marker='x')
plt.plot(matrix_double_spread_BLIS[:, 0], matrix_double_spread_BLIS[:, 4], label='spread, BLIS', color='green', marker='2', markersize=10)
plt.plot(matrix_double_close_MKL[:, 0], matrix_double_close_MKL[:, 4], label='close, MKL', color='pink', marker='D')
plt.plot(matrix_double_close_openBLAS[:, 0], matrix_double_close_openBLAS[:, 4], label='close, OpenBLAS', color='black', marker='*', markersize=7)
plt.plot(matrix_double_close_BLIS[:, 0], matrix_double_close_BLIS[:, 4], label='close, BLIS', color='purple', marker='s')
plt.legend(loc='upper right')
plt.grid(True, linestyle='--', color='gray')
plt.xlabel('Number of available cores')
plt.ylabel('Elapsed time (seconds)')
plt.title("GEMM calculation with increasing number of available cores (THIN node, double precision)")
plt.show()


# Plot of GFLOPS
plt.plot(matrix_single_spread_MKL[:, 0], matrix_single_spread_MKL[:, 5], label='spread, MKL', color='blue', marker='o')
plt.plot(matrix_single_spread_openBLAS[:, 0], matrix_single_spread_openBLAS[:, 5], label='spread, OpenBLAS', color='red', marker='x')
plt.plot(matrix_single_spread_BLIS[:, 0], matrix_single_spread_BLIS[:, 5], label='spread, BLIS', color='green', marker='2', markersize=10)
plt.plot(matrix_single_close_MKL[:, 0], matrix_single_close_MKL[:, 5], label='close, MKL', color='pink', marker='D')
plt.plot(matrix_single_close_openBLAS[:, 0], matrix_single_close_openBLAS[:, 5], label='close, OpenBLAS', color='black', marker='*', markersize=7)
plt.plot(matrix_single_close_BLIS[:, 0], matrix_single_close_BLIS[:, 5], label='close, BLIS', color='purple', marker='s')
plt.legend(loc='upper left')
plt.grid(True, linestyle='--', color='gray')
plt.xlabel('Number of available cores')
plt.ylabel('GFLOPS')
plt.title("GEMM calculation with increasing number of available cores (THIN node, single precision)")
plt.show()


plt.plot(matrix_double_spread_MKL[:, 0], matrix_double_spread_MKL[:, 5], label='spread, MKL', color='blue', marker='o')
plt.plot(matrix_double_spread_openBLAS[:, 0], matrix_double_spread_openBLAS[:, 5], label='spread, OpenBLAS', color='red', marker='x')
plt.plot(matrix_double_spread_BLIS[:, 0], matrix_double_spread_BLIS[:, 5], label='spread, BLIS', color='green', marker='2', markersize=10)
plt.plot(matrix_double_close_MKL[:, 0], matrix_double_close_MKL[:, 5], label='close, MKL', color='pink', marker='D')
plt.plot(matrix_double_close_openBLAS[:, 0], matrix_double_close_openBLAS[:, 5], label='close, OpenBLAS', color='black', marker='*', markersize=7)
plt.plot(matrix_double_close_BLIS[:, 0], matrix_double_close_BLIS[:, 5], label='close, BLIS', color='purple', marker='s')
plt.legend(loc='upper left')
plt.grid(True, linestyle='--', color='gray')
plt.xlabel('Number of available cores')
plt.ylabel('GFLOPS')
plt.title("GEMM calculation with increasing number of available cores (THIN node, double precision)")
plt.show()




