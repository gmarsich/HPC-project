void* read_pgm_image(int* xsize,int*ysize,const char*image_name){
void* image;
char c;
*xsize=0;
*ysize=0;
FILE* image_file;
char*line=NULL;// pointer che conterra la matrice rappresentante l'immagine
size_t k=0,n=0;// size_t è una variabile apposita per rappresentare la size IN BYTES delle variabili
image_file=fopen(image_name,"r");
// getline(&buffer,&sizebuffer,std) assegna al buffer di size=sizebuffer quello letto nel std indicato e poi restituisce la size della riga in considerazione
for (int i=0;i<4;i++)
  k=getline( &line, &n, image_file);// skippo l'header


sscanf(line,"%d %d", ysize, xsize);// ora mi trovo nella riga contenente le dimensioni e le leggo asseegnandole alle apposite variabili
k=getline( &line, &n, image_file);//ora mi trovo nella riga contenente max_value ma non ci serve
for(int i=0;i<xsize*ysize-1;i++){// ora mi trovo nella riga contenente i valori dei pixels
    
}
image=(void*)line;// assegna al pointer image il valore del pointer line che in questo caso sarà l'inizio della stringa contenente i valori dei pixels
fclose(image_file);
return image;
};
