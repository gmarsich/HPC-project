#include<getopt.h>
#include <time.h>
#include<omp.h>
#include <dirent.h>
#include <mpi.h>
#include<header_general.h>
#include<header_update_rules.h>








int main(int argc,char**argv){
    MPI_Status status;
    MPI_Request request_upper_s,request_lower_s,request_upper_r,request_lower_r;
    double time=0.0,end,begin;
    char* Grid;
    char* cells;
    char* upper;
    char* lower;
    char* New;
    char* nome=NULL;
    char filename[50];
    int x,y,total_size=100,dimension,iteration=10,cell_size,cell_dim=1,print=0,rank,size,mpi_provided_thread_level,n_threads,mean=5;
    bool scale=false;
    int opt;
    void*image;
    char create;
    MPI_Init_thread( &argc, &argv,MPI_THREAD_FUNNELED,&mpi_provided_thread_level );
    MPI_Comm_rank( MPI_COMM_WORLD,&rank);
    MPI_Comm_size( MPI_COMM_WORLD,&size );


    if(rank==0)
    printf("----------------------------------------------------------------------\n");
    while((opt = getopt(argc, argv, ":k:n:f:s:c:ire")) != -1)// getopt() restituisce i seguenti valori :
                                                    // -1: se non ha più opzioni da riconoscere
                                                                    // (le opzioni sono passate con -option)
                                                    // ?: se non riconosce l'opzione tra quelle indicate o se non è specificato un volore all'opzione che lo richiederebbe
                                                    // :: se nella stringa che specifica le opzioni si inserisce come primo char : allora se manca un valore ad un opzione che lo richiederebbe restituisce come valore : anzichè ?
                                                    // se un'opzione viene riconosciuta allora la variabile esterna optarg avrà tale valore come char
                                                    // per indicare che un opzione necessita di un valore si inserisce : dopo l'opzione

    {
        switch(opt)
        {
            case 'k':
                total_size=atoi(optarg);
                if(rank==0)
                printf("Recived size of %s\n",optarg);
                break;
            case 'n':
                if(rank==0)
                printf("Number of evolution steps: %s\n",optarg);
                iteration=atoi(optarg);
                break;
            case 'i':
                if(rank==0)
                printf("Creating the initial set_up\n");
                create='i';
                break;
                
            case 'r':
                if(rank==0)
                printf("Running the evolution \n");
                create='r';
                break;

             case 'e':
                if(rank==0)
                printf("Ordered evolution setted on \n");
                create='e';
                break;

            case 's':
                if(rank==0)
                printf("Print the results every %s\n",optarg);
                print=atoi(optarg);
                break;
            case 'c':
                if(rank==0)
                printf("Cell size of: %s\n",optarg);
                cell_size=atoi(optarg);
                cell_dim=cell_size*cell_size;
                scale=true;
                break;

            case 'f':
                if(rank==0)
                printf("File Name:%s\n",optarg);
                nome=optarg;
                
                break;

            case '?':
                if(rank==0)
                printf("Option %c not existing \n",optopt);// optopt è la variabile esterna che punta all'opzione letta
                return 1;

            case ':':
              if(rank==0)
              printf("The option %c needs an argument\n",optopt);
              return 1;
        }
    }

//check if the user specified a file 
if (nome==NULL){
if(rank==0)
printf("File name not specified\n");
 return 1;}

//Initialization mode
  if(create=='i'){
    x=total_size/size;
    y=total_size;
    if (total_size%size!=0&rank==(size-1)){x=x+total_size%size;}
    image=create_image(x,y,total_size,rank);
    if(rank==0){
    image=realloc(image,sizeof(char)*total_size*total_size);
        for(int k=1;k<size;k++)
        MPI_Recv(image+x*y*k,(k==size-1)?((x+total_size%size)*y):(x*y), MPI_CHAR,k,0,MPI_COMM_WORLD,&status);
         write_pgm_image(image,total_size,total_size,nome);
          printf("Created the initial set_up of dimension %dx%d\n",total_size,total_size);
    }
    if(rank!=0){MPI_Ssend(image,x*y, MPI_CHAR,0,0,MPI_COMM_WORLD);}
    MPI_Finalize();
    return 0;
  }


//Static Evolution
if (create=='r'){
if(file_exists(nome)==false){
    if(rank==0)
    printf("Specified file name not existing\n");
    return 1;}

if(rank==0){
// DELETING ALL THE PRECEDENT FILES IN THE results_serial and results_parallel directories 
 DIR *theFolder = opendir("./results");
    struct dirent *next_file;
    char filepath[256];

    while ( (next_file = readdir(theFolder)) != NULL )
    {
        // build the path for each file in the folder
        sprintf(filepath, "%s/%s", "./results", next_file->d_name);
        remove(filepath);
    }
    closedir(theFolder);
}








image=read_pgm_image(&total_size,&total_size,nome);
if(size>total_size){
    if(rank==0)
    printf("NUMBER OF PROCESSES HIGHER THEN THE NUMBER OF ROWS\n");
    return 1;}
if(rank==0)
    printf("Used the image %s of dimension %dx%d\n",nome,total_size,total_size);
if (print==0){print=iteration;}
for(int t=0;t<mean;t++){


  x=total_size/size;
  y=total_size;



  Grid= ((char*)image+rank*x*y);
  if (total_size%size!=0&rank==(size-1)){x=x+total_size%size;}

  dimension=x*y;
upper=(char*)calloc(y,sizeof(char));    
lower=(char*)calloc(y,sizeof(char));
MPI_Barrier(MPI_COMM_WORLD);
if(t==0)
begin=MPI_Wtime();
for(int k=1;k<iteration+1;k++){
  New=(char*)calloc( dimension, sizeof(char) );

  //update the image exept the border
#pragma omp parallel 
{n_threads=omp_get_num_threads();
#pragma omp master
{if (k==1&t==0)
printf("Process %d spawn %d threads\n",rank,n_threads);}
#pragma omp for schedule(static)
  for(int i=1;i<(x-1);i++){
      for(int j=0;j<(y);j++){
        updateCell(i,j,y,Grid,New);


    }
  }
}



//passing and recieving the upper and lower buffers
MPI_Isend(Grid+(x-1)*y, y, MPI_CHAR,(rank+1<size)?(rank+1):0,1,MPI_COMM_WORLD,&request_upper_s);
MPI_Irecv(lower, y, MPI_CHAR,(rank+1<size)?(rank+1):0,0,MPI_COMM_WORLD,&request_lower_r);

MPI_Isend(Grid, y, MPI_CHAR,(rank-1>=0)?(rank-1):(size-1),0,MPI_COMM_WORLD,&request_lower_s);
MPI_Irecv(upper,y, MPI_CHAR,(rank-1>=0)?(rank-1):(size-1),1,MPI_COMM_WORLD,&request_upper_r);


MPI_Wait(&request_upper_s, &status);
MPI_Wait(&request_lower_r, &status);

MPI_Wait(&request_lower_s, &status);
MPI_Wait(&request_upper_r, &status);

//update the border
if(x>1){
for(int j=0;j<(y);j++){
  updateUP(j,x,y,Grid,New,upper);
  updateDOWN(j,x,y,Grid,New,lower);
}
}
else if(x==1){
for(int j=0;j<(y);j++)
    update1LINE(j,x,y,Grid,New,upper,lower);
}


Grid=NULL;
Grid=New;
New=NULL;
//writing the results
if(k%print==0 ){
if(rank==0){
    Grid=realloc(Grid,sizeof(char)*total_size*total_size);
        for(int z=1;z<size;z++)
        MPI_Recv(Grid+x*y*z,(z==size-1)?((x+total_size%size)*y):(x*y), MPI_CHAR,z,0,MPI_COMM_WORLD,&status);
    if(scale==false){
    sprintf(filename,"./results/result%d.pgm",k);
    write_pgm_image((void*) Grid,total_size,total_size,filename);
    }
    if(scale==true){
        cells=(char*)calloc(total_size*total_size*cell_dim,sizeof(char));
        for(int i=0;i<total_size;i++) {
            for(int j=0;j<total_size;j++){
                color(cells,Grid,cell_size,total_size,i,j);
             }
        }
        sprintf(filename,"./results/result%d.pgm",k);
        write_pgm_image((void*)cells,total_size*cell_size,total_size*cell_size,filename);
        free (cells);

    }   
}

if(rank!=0){MPI_Ssend(Grid,x*y, MPI_CHAR,0,0,MPI_COMM_WORLD);}

}


}
MPI_Barrier(MPI_COMM_WORLD);
end=MPI_Wtime();
time=time+(end-begin);}
if(rank==0){
printf("write done\n");// Avviso della fine scrittura
printf("Avarage time taken to the process: %f\n",time/mean);
//writing on data.txt
if(file_exists("data.txt")==true){
FILE* output;
output=fopen("data.txt","a");// Apro un file per scriverci
fprintf(output,"%d\t%d\t%f\n",n_threads,size,time/mean);// Scrivo nel file l'header
fclose(output);}
else{FILE* output;
output=fopen("data.txt","a");// Apro un file per scriverci
fprintf(output,"#DATA GENERETED WITH DIMENSION %d and iteration %d\n#Threads|MPItask|time\n%d\t%d\t%f\n",total_size,iteration,n_threads,size,time/mean);// Scrivo nel file l'header
fclose(output);
}
}
free(Grid);
free(image);
MPI_Finalize();
return 0;
}




//ordered evolution
if(create=='e'){
if(file_exists(nome)==false&rank==0){
    if(rank==0)
    printf("File Name not found\n");
    return 1;}
if(rank==0){
// DELETING ALL THE PRECEDENT FILES IN THE results_serial and results_parallel directories 
 DIR *theFolder = opendir("./results");
    struct dirent *next_file;
    char filepath[256];

    while ( (next_file = readdir(theFolder)) != NULL )
    {
        // build the path for each file in the folder
        sprintf(filepath, "%s/%s", "./results", next_file->d_name);
        remove(filepath);
    }
    closedir(theFolder);
}








image=read_pgm_image(&total_size,&total_size,nome);
if(rank==0)
    printf("Used the image %s with dimension %dx%d\n",nome,total_size,total_size);
if (print==0){print=iteration;}
x=total_size/size;
  y=total_size;



  Grid=(void*) ((char*)image+rank*x*y);
  if (total_size%size!=0&rank==(size-1)){x=x+total_size%size;}
  dimension=x*y;
MPI_Barrier(MPI_COMM_WORLD);
if(rank==0)
    printf("Starting ordered evolution\n");


for(int k=1;k<iteration+1;k++){
New=(char*)calloc( dimension, sizeof(char) );
New=Grid;
upper=(char*)calloc(y,sizeof(char));
lower=(char*)calloc(y,sizeof(char));
 
if(rank==size-1){
    MPI_Ssend(Grid+(x-1)*y, y, MPI_CHAR,0,1,MPI_COMM_WORLD);
    MPI_Recv(lower, y, MPI_CHAR,0,0,MPI_COMM_WORLD,&status);
    }
 if(rank!=0)
    MPI_Ssend(Grid, y, MPI_CHAR,(rank-1>=0)?(rank-1):(size-1),0,MPI_COMM_WORLD);

MPI_Recv(upper,y, MPI_CHAR,(rank-1>=0)?(rank-1):(size-1),1,MPI_COMM_WORLD,&status);
if(x>1){
for(int j=0;j<(y);j++){
  updateUP(j,x,y,New,New,upper);
}
if(rank==0)
    MPI_Ssend(Grid, y, MPI_CHAR,(size-1),0,MPI_COMM_WORLD);

  //update the image exept the border

  for(int i=1;i<(x-1);i++){
      for(int j=0;j<(y);j++){
        updateCell(i,j,y,New,New);


    }
  }
}
if(rank!=(size-1))
    MPI_Recv(lower, y, MPI_CHAR,(rank+1<size)?(rank+1):0,0,MPI_COMM_WORLD,&status);

//update the border
for(int j=0;j<(y);j++){
if(x==1){update1LINE(j,x,y,New,New,upper,lower);}
else{updateDOWN(j,x,y,New,New,lower);}
}
if(rank==0 & x==1)
    MPI_Ssend(Grid, y, MPI_CHAR,(size-1),0,MPI_COMM_WORLD);
if(rank!=(size-1))
    MPI_Ssend(Grid+(x-1)*y, y, MPI_CHAR,(rank+1),1,MPI_COMM_WORLD);


Grid=NULL;
Grid=New;
New=NULL;


if(k%print==0 ){
if(rank==0){
    Grid=realloc(Grid,sizeof(char)*total_size*total_size);
        for(int z=1;z<size;z++)
        MPI_Recv(Grid+x*y*z,(z==size-1)?((x+total_size%size)*y):(x*y), MPI_CHAR,z,0,MPI_COMM_WORLD,&status);
    if(scale==false){
    sprintf(filename,"./results/result%d.pgm",k);
    write_pgm_image((void*) Grid,total_size,total_size,filename);
    }
    if(scale==true){
        cells=(char*)calloc(total_size*total_size*cell_dim,sizeof(char));
        for(int i=0;i<total_size;i++) {
            for(int j=0;j<total_size;j++){
                color(cells,Grid,cell_size,total_size,i,j);
             }
        }
        sprintf(filename,"./results/result%d.pgm",k);
        write_pgm_image((void*)cells,total_size*cell_size,total_size*cell_size,filename);
        free (cells);

    }   
}

if(rank!=0){MPI_Ssend(Grid,x*y, MPI_CHAR,0,0,MPI_COMM_WORLD);}

}


if (rank==0)
    printf("Write done\n");
free(image);
MPI_Finalize();
return 0;

}

}
}
