#include<header_converter.h>





int main(int argc,char**argv){
char* image;
char* cells;
int x,y,cell_dim=1,cell_size;
x=atoi(argv[1]);
y=atoi(argv[2]);
cell_size=atoi(argv[3]);
cell_dim=cell_size*cell_size;
/*if(x*y%cell_dim!=0){printf("Dimensioni incompatibili\n");return 1;}*/
image=read_text_image(x,y,"set_up.txt");
for (int i=0;i<x;i++){
    for(int j=0;j<y;j++)
    printf("%c",image[j+i*y]);
printf("\n");
}



for(int i=0;i<x;i++){
    for(int j=0 ;j<y;j++){
        image[j+i*y]=(image[j+i*y]=='O')?(char)0:(char)255;
    }
}

cells=(char*)calloc(x*y*cell_dim,sizeof(char));
for(int i=0;i<x;i++) {
    for(int j=0;j<y;j++){
        color(cells,image,cell_size,x,i,j);
    }
}



write_pgm_image((void*) cells,cell_size*y,cell_size*x,"grid_scaled.pgm");
write_pgm_image((void*) image,y,x,"grid.pgm");
free(image);
free(cells);
/*image=read_pgm_image(&x,&y,"prova.pgm");
swap(image,x,y);
write_pgm_image(image,x,y,"replica.pgm");
free(image);*/
return 0;
}


