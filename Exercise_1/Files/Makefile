#This is a makefile, use the comand make on the directory where all the files are 
#(be sure all the files are presenet:all the headers [header_general.h,header_update_rules.h,header_converter.h],game_of_life.c and converter.c)
#The make file will also create the folder results where all the results of the evolution are saved;
#!!BE SURE TO CREATE AGAIN SUCH FOLDER IF U WISH TO RUN THE CODE ON A DIFFERENT DIRECTORY!!
#---------------------------------------------------------------------------------
#This are the used compilers (Be sure to have installed mpicc and gcc, if u wish to use other compiler change theese variables)
COMPILER_MAIN=mpicc
COMPILER_CONVERTER=gcc
#This is the headers directory 
INCDIR=./headers 
#theese are all the option passed to the compilers 
MPICCFLAGS=$(MAIN).c -I$(INCDIR)  -fopenmp
GCCFLAGS=converter.c -I$(INCDIR)
#This is the name of the main file 
MAIN=game_of_life


game_of_life.x: results
	$(COMPILER_MAIN) $(MPICCFLAGS) -o $@
	
converter.x:
	$(COMPILER_CONVERTER) $(GCCFLAGS) -o $@
	

results: converter.x
	mkdir $@
	
# use the command make clean to clear all the compiled programs , the folder and files created 
clean:
	rm -rf *.x results data.txt *.pgm

