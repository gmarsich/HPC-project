import os
import pandas as pd
import numpy as np


def mean_matrix(csv_directory):

    # get the dimensions of the 3D matrix: 1° dim: number of tests; 2° dim: number of steps; 3°: number of retained values
    file_path = os.path.join(csv_directory, os.listdir(csv_directory)[0])
    df = pd.read_csv(file_path, header=None)
    matrix_numpy = df.to_numpy()

    # initialise the 3D matrix with zeros
    matrix = np.zeros((len(os.listdir(csv_directory)), matrix_numpy.shape[0], matrix_numpy.shape[1]))

    # save the contents of the csv files in the 3D matrix
    i = -1
    for filename in os.listdir(csv_directory): # OBS.: observe that the order is somehow random
        i+=1
        file_path = os.path.join(csv_directory, filename)

        # copy the data of the csv file in a dataframe
        df = pd.read_csv(file_path, header=None)
        matrix_numpy = df.to_numpy()
        matrix[i] = matrix_numpy

    # get the matrix containing the means across the tests
    mean_matrix = np.mean(matrix, axis=0) # OBS.: the first three or four columns, containing the values of (number cores,) M, N and K, are "left untouched" by the mean operation since across axis 0 they are all equal
    return mean_matrix
    