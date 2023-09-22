## Exercise 2
This is the folder containing all the files regarding the Exercise 2 for the final project of HPC. 


The content of this folder is the following: 
| Item      | Description |
| :---        |    :----:   |
| Graphs      | Folder containing all the files needed for the compilation       |
| RESULTS   | Folder containing some initial configurations used to check the correctness of the program|
|bash_scripts | Folder containing all the data generated during the scalability studies | 

### Compilation of the program 
To compile the program ensure first to have downloaded the gcc and mpicc compilers (on ORFEO load the compilers with the command `module load openMPI/4.1.5/gnu/12.2.1`). If someone wish to change compilers remember to change them into the Make file. 

To run the compilation just use the command `make` inside the Files folder. 

After the compilation the following files and folder will be created: 
1. game_of_life.x: executable of the program game_of_life
2. converter.x: executable of the converter program
3. results: folder required to the game_of_life program to write the results

**(!NOTE: if you wish to run the executable game_of_life.x on a different directory remember to move also the results folder!)**

### Execution of the program 
1.The *converter.x* executable is used to produce an image from an arbitrary grid set up built in the set_up.txt file. To create the configuration use . to denote dead cells and O (big o) do denote an alive cell. After creating the configuration in the set_up.txt file run the program as follow: 

`./converter.x <number_of_rows> <number_of_columns> <cell_size>` 

The program will create two images representing the original and scaled version of the desired grid configuration. This program was meanly used to check the correctness of the game_of_life program. 

2.The *game_of_life.x* executable is the parallelized implementation of the game of life. It has the following options:
- `-i` to run the initialization mode and produce an initial set_up (See the report for more details on the initial configuration)
- `-k <size>` to specify the size of the square grid initial set up
- `-f <file_name>` to specify the name of the output for the configuration or to specify the name of the initial set_up for the evolution mode
- `-r` to run the evolution mode
- `-n <iteration>` to specify the number of evolution steps
- `-s <frequency>` to specify the frequency to return the result of the current step evolution
- `-e` to run the ordered evolution (by default it runs the static evolution)
- `-c <cell_size>` to print the results in a scaled version with each cell of dimension cell_size x cell_size (meanly used to check the correctness of the program)



To execute the program use the mpirun command as follow



`mpirun <mpirun_options> ./game_of_life.x <game_of_life_options>`



Remember that the program is an hybrid parallelization and to specify the number of openMP threads each MPI process will spawn use the environmental variable OMP_NUM_THREADS with `export OMP_NUM_THREADS=<number_of_threads_per_process>`. 

### Data generated 
As the program game_of_life finish it's evolution, a file *data.txt* is created and inside it's saved the number of generated threads , the number of MPI processes and the mean of the time taken by the evolution. If the file already exist all those data are appended into such file. 


This file can be used to plot a scalability study with gnuplot. The data used for our scalability studies and the gnuplot script are present in the data folder. 


The results of the evolution are instead saved on the folder results which is resetted every new run of the program. 


The program will also print on the standard output some useful information like the option taken , the number of MPI processes and the number of openMP threads. 

### Sbatch scripts
The sbatch scripts can be used to generate the data required for the scalability studies. They can be found on the sbatch_script folder and can be used by moving them into the Files folder and running the command `sbatch <sbatch_script>`.  
They are :
- slurm_grid_openmp.job: used to produce the openMP scalability datas
- slurm_grid_MPI_strong.job: used to produce the strong MPI scalability datas
- slurm_grid_MPI_weak.job: used to produce the weak MPI scalability datas
- slurm_grid_serial.job: used to produce the serial time for the 3 studied dimensioons in the openMP scalability

The job will also create an *output_job.out* file to save all the standard outputs. 
