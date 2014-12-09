#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <time.h>  

 
#include <ctype.h>

#include <stdlib.h>

#include <unistd.h> /* for getopt */

#include "cargarchivo.h"

#include "cargarchivo.h"

#define N 100000

int calcular(char *a);

int main(int argc, char *argv[])
{
    char a[N];    
    clock_t start = clock(); 
    int index;
    int c;
    
    opterr = 0;
    
    while ((c = getopt (argc, argv, "f:")) != -1)
        switch (c)
    {
        case 'f':
            printf("Leyendo archivo[%s]...\n", optarg);

            FILE *archivo;
            char mensaje;
            int n;
            int i=0;
            char* str;
            
            archivo = fopen(optarg,"r");
            
            if(archivo == NULL){
                printf("\nError al abrir el archivo");
            } else {
                 while (feof(archivo)==0){
                    str=(char *) malloc(99*sizeof(char));
                    fgets(str,99,archivo);
                    a[i]=str[0];
                    i++;           
                }
            }
            fclose(archivo);
            
            printf("%i\n",calcular(a));
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
    

    printf("\nTiempo transcurrido: %f\n  ", ((double)clock() - start) / CLOCKS_PER_SEC);
    return 0;
}

int calcular(char *a){
    int acc = 0;
    int i;
    for( i = 0; i < N - 1; i++)
    {

        if(a[i]==0)break;//corta el ciclo cuando el arreglo no tiene mas valores validos;
        printf("%c  ",a[i]);
        if(i%4==3)printf("\n");
       char tmp = a[i] ^ a[i + 1];
       acc = acc + tmp;
    }

    return acc;
}
