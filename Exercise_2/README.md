## Exercise 2
This is the folder containing all the files regarding the Exercise 2 for the final project of HPC. The computations have been performed on a `THIN` node.


The content of this folder is the following: 
| Item      | Description |
| :---        |    :----:   |
| Graphs      | Folder containing the programs used to create the graphs and the plots that we obtained      |
| RESULTS   | Folder containing, by the means of a structure of nested folders, the results we collected from the execution of the tests|
|bash_scripts | Folder containing the four bash scripts we used to automate the process of collecting the results | 
|Makefile_double | File, a Makefile to generate the executables from `gemm_MOD.c`, having double precision| 
|Makefile_single | File, a Makefile to generate the executables from `gemm_MOD.c`, having single precision| 
|gemm_MOD.c | File, the level 3 BLAS function from which we collected the results | 

### Compilation of the program 
First of all reserve the resources on ORFEO with: `salloc --exclusive -n 12 -N1 -p THIN --time=2:0:0`
To compile the program you need of course to have loaded the necessary modules: `module load architecture/Intel`, `module load mkl` and `module load openBLAS/0.3.23-omp`.
Then, set the environmental variables: `export OMP_PLACES=cores`, `OMP_PROC_BIND` as either `export OMP_PROC_BIND=spread` or `export OMP_PROC_BIND=close`, `export BLIS_NUM_THREADS=12` and `export LD_LIBRARY_PATH={path_for_blis}:$LD_LIBRARY_PATH` (where `{path_for_blis}` has to be replaced with the path to the `lib` folder of BLIS, so the system will search for libraries also in that directory)

You should have the bash script (you have to make it executable with `chmod +x {bash_script}`, where `{bash_script}` is the name of the bash script) and the `Makefile` you are interested in the same folder as the `gemm_MOD.c` file.
Typing `srun -n1 make cpu` you will create the following files: 
1. gemm_mkl.x: to be used with the MKL library
2. gemm_oblas.x: to be used with the OpenBLAS library
3. gemm_blis.x: to be used with the BLIS library

