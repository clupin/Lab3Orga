#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h> /* for getopt */


#include "cargarchivo.h"



#define N 400

void funcion(float f[]);
float* leerArchivo (char *direccion);

int main (int argc, char **argv)
{
    int aflag = 0;
    int bflag = 0;
    char *cvalue = NULL;
    int index;
    int c;
    
    opterr = 0;
    
    while ((c = getopt (argc, argv, "f:")) != -1)
        switch (c)
    {
        case 'f':
            printf("a un paso de lograrlo : %s\n", optarg);
            float *F=leerArchivo(optarg);
            funcion(F);
            break;
        case '?':
            if (optopt == 'f')
                fprintf (stderr, "Opcion -%c requiere la direccion del archivo.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr,
                         "Unknown option character `\\x%x'.\n",
                         optopt);
            return 1;
        default:
            abort ();
    }
    
    for (index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);
    return 0;
}

void funcion(float f[]){
    printf("%f  %f  %f \n",f[0],f[1],f[2]);
}
float* leerArchivo (char *direccion){
    
    FILE *archivo;
    char mensaje;
    float lista[100000];
    int n;
    int i=0;
    
    archivo = fopen(direccion,"r");
    
    if(archivo == NULL){
        printf("\nError al abrir el archivo");
    } else {
        while (feof(archivo)==0){
            mensaje = fgetc(archivo);
            lista[i]= atoi(&mensaje);
            mensaje = fgetc(archivo);
            i++;
        }
    }
    fclose(archivo);
    
    return lista;
}