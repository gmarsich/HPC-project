#ifndef HEADER_UPDATE
#define HEADER_UPDATE
#include <stdlib.h>
#include<stdio.h>







//Function to update the center
void updateCell(const int row,const int col,const int y_size,char*OldGrid,char*NewGrid){
    char alive=(char) 0;
    short int lives=0;              //counting the alive neighbours
    int dim=y_size;


if(col==0){
    for(int i=(row-1);i<(row+2);i=i+2){             //Check the row up and down 
            for(int j=(col);j<(col+2);j++){
                if(OldGrid[j+i*dim]==alive){
                    lives+=1;
                }
            }
            if(OldGrid[(y_size-1)+i*dim]==alive)       //check the extremes 
                lives+=1;
        }

if(OldGrid[(col+1)+row*dim]==alive)             // check the central line
lives+=1;

if(OldGrid[(y_size-1)+row*dim]==alive)
lives+=1;
}
else if(col==(y_size-1)){                       //specular case of before
for(int i=(row-1);i<(row+2);i=i+2){
            for(int j=(col-1);j<(col+1);j++){
                if(OldGrid[j+i*dim]==alive){
                    lives+=1;
                }
            }
            if(OldGrid[i*dim]==alive)
                lives+=1;
        }

if(OldGrid[(col-1)+row*dim]==alive)
lives+=1;
if(OldGrid[row*dim]==alive)
lives+=1;
}

else{
        for(int i=(row-1);i<(row+2);i=i+2){             //check the line up and down
            for(int j=(col-1);j<(col+2);j++){
                if(OldGrid[j+i*dim]==alive){
                    lives+=1;
                }
            }
        }

        for(int j=(col-1);j<(col+2);j=j+2){             //check the central line
            if(OldGrid[j+row*dim]==alive){
                lives+=1;
            }
        }
}

NewGrid[col+row*dim]=(lives==3 | lives==2)?alive:(char)255;     //Update 
};

//Function to update the first line 
void updateUP(const int col,const int x_size,const int y_size,char*OldGrid,char*NewGrid,char* upper){
   char alive=(char) 0;
   const int row=0;
    short int lives=0;
    int dim=y_size;


if(col==0){
    if(OldGrid[1]==alive)           //central line
                lives+=1;
    if(OldGrid[(y_size-1)]==alive)
                lives+=1;
    for(int j=(col);j<(col+2);j++){        //line below
        if(OldGrid[j+(row+1)*dim]==alive)
            lives+=1;
        }
            if(OldGrid[(y_size-1)+(row+1)*dim]==alive)  //riga sotto esterno
                lives+=1;
    for(int j=(col);j<(col+2);j++){          //upper line   
        if(upper[j]==alive)
            lives+=1;
        }
            if(upper[(y_size-1)]==alive) 
                lives+=1;                               // upper's extreme

}

else if(col==(y_size-1)){               //analogous but specular
    if(OldGrid[0]==alive)
                lives+=1;
    if(OldGrid[(y_size-2)]==alive)
                lives+=1;
    for(int j=(col-1);j<(col+1);j++){
        if(OldGrid[j+(row+1)*dim]==alive)
            lives+=1;
        }
            if(OldGrid[(row+1)*dim]==alive)
                lives+=1;
    for(int j=(col-1);j<(col+1);j++){                   
        if(upper[j]==alive)
            lives+=1;
        }
            if(upper[0]==alive)
                lives+=1;                              
}

else{
for(int j=(col-1);j<(col+2);j=j+2){     //central line
   if(OldGrid[j+row*dim]==alive){
      lives+=1;
    }
}
for(int j=(col-1);j<(col+2);j++){       //lower line
   if(OldGrid[j+(row+1)*dim]==alive){
      lives+=1;
    }
}
for(int j=(col-1);j<(col+2);j++){                       //upper line
   if(upper[j]==alive){
      lives+=1;
    }                                                   
}
}
NewGrid[col+row*dim]=(lives==3 | lives==2)?alive:(char)255;//Update

};

//Function to update the last line 
void updateDOWN(const int col,const int x_size,const int y_size,char*OldGrid,char*NewGrid,char* lower){
   char alive=(char) 0;
   const int row=(x_size-1);
    short int lives=0;
    int dim=y_size;

 if(col==0){
    if(OldGrid[1+row*dim]==alive)
                lives+=1;
    if(OldGrid[(y_size-1)+row*dim]==alive)
                lives+=1;
    for(int j=(col);j<(col+2);j++){
        if(OldGrid[j+(row-1)*dim]==alive)
            lives+=1;
        }
            if(OldGrid[(y_size-1)+(row-1)*dim]==alive)
                lives+=1;
    for(int j=(col);j<(col+2);j++){                 //PEZZO DA CAMBIARE PER MPI (CONSIDERA LA PRIMA LINEA COME QUELLA SOTTO) 
        if(lower[j]==alive)
            lives+=1;
        }
            if(lower[(y_size-1)]==alive)
                lives+=1;                           //FINE PEZZO

}

else if(col==(y_size-1)){
    if(OldGrid[row*dim]==alive)
                lives+=1;
    if(OldGrid[(y_size-2)+row*dim]==alive)
                lives+=1;
    for(int j=(col-1);j<(col+1);j++){
        if(OldGrid[j+(row-1)*dim]==alive)
            lives+=1;
        }
            if(OldGrid[(row-1)*dim]==alive)
                lives+=1;
    for(int j=(col-1);j<(col+1);j++){                    //PEZZO DA CAMBIARE PER MPI (CONSIDERA LA PRIMA LINEA COME QUELLA SOTTO) 
        if(lower[j]==alive)
            lives+=1;
        }
            if(lower[0]==alive)
                lives+=1;                                 //FINE PEZZO  
}

else{
    for(int j=(col-1);j<(col+2);j=j+2){
        if(OldGrid[j+row*dim]==alive){
        lives+=1;
    }
}
for(int j=(col-1);j<(col+2);j++){
   if(OldGrid[j+(row-1)*dim]==alive){
      lives+=1;
    }
}
for(int j=(col-1);j<(col+2);j++){                    
   if(lower[j]==alive){
      lives+=1;
    }                                               
}                                                  
}
NewGrid[col+row*dim]=(lives==3 | lives==2)?alive:(char)255;

};

//Function for the case in wich a process has 1 line only 
void update1LINE(const int col,const int x_size,const int y_size,char*OldGrid,char*NewGrid,char* upper,char* lower){
   char alive=(char) 0;
   const int row=0;
    short int lives=0;
    int dim=y_size;


if(col==0){
    if(OldGrid[1]==alive)
                lives+=1;
    if(OldGrid[(y_size-1)]==alive)
                lives+=1;
    for(int j=(col);j<(col+2);j++){
        if(lower[j]==alive)
            lives+=1;
        }
            if(lower[(y_size-1)]==alive)
                lives+=1;
    for(int j=(col);j<(col+2);j++){             
        if(upper[j]==alive)
            lives+=1;
        }
            if(upper[(y_size-1)]==alive) 
                lives+=1;                              

}

else if(col==(y_size-1)){
    if(OldGrid[0]==alive)
                lives+=1;
    if(OldGrid[(y_size-2)]==alive)
                lives+=1;
    for(int j=(col-1);j<(col+1);j++){
        if(lower[j]==alive)
            lives+=1;
        }
            if(lower[0]==alive)
                lives+=1;
    for(int j=(col-1);j<(col+1);j++){                  
        if(upper[j]==alive)
            lives+=1;
        }
            if(upper[0]==alive)
                lives+=1;                              
}

else{
for(int j=(col-1);j<(col+2);j=j+2){
   if(OldGrid[j+row*dim]==alive){
      lives+=1;
    }
}
for(int j=(col-1);j<(col+2);j++){
   if(lower[j]==alive){
      lives+=1;
    }
}
for(int j=(col-1);j<(col+2);j++){                       
   if(upper[j]==alive){
      lives+=1;
    }                                                  
}
}
NewGrid[col+row*dim]=(lives==3 | lives==2)?alive:(char)255;

};


#endif
