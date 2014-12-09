#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <time.h>  

 
#include <ctype.h>

#include <stdlib.h>

#include <unistd.h> /* for getopt */

#include "cargarchivo.h"


#define N 100000


float calcular(float *a, float *b);

int main(int argc, char *argv[])
{
    clock_t start = clock();
    float a[N];
    float b[N];
    int index;
    int c;
    int i;
    

    opterr = 0;
    
    while ((c = getopt (argc, argv, "f:")) != -1)
        switch (c)
    {
        case 'f':
            printf("Leyendo archivo[%s]...\n", optarg);
            float *F=leerArchivo(optarg);
            //for (i; F[i]!=0; i++) printf("i  |  %f\n",F[i]);
            for(i = 0; i < N; i++)a[i] = F[i];
            
            for(i = 0; i < N; i++) b[i] = F[i];
            printf("%f\n",calcular(a,b));
            break;
        case '?':
            if (optopt == 'f')
                fprintf (stderr, "Opcion -%c requiere la direccion del archivo.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n Seleccione la Opcion -f <filepath> \n", optopt);
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
    
    printf("Tiempo transcurrido: %f", ((double)clock() - start) / CLOCKS_PER_SEC);
    return 0;


}

float calcular(float *a, float *b){

    float acc = 0;
    float acc2 = 0;
    int i;
    for( i = 0; i < N; i++){
        if(a[i]==0)break;//corta el ciclo cuando el arreglo no tiene mas valores validos;
        acc = acc + a[i] / 2 + sqrt(b[i]);
    }
    printf("%f\n", acc);
    for(i = 0; i < N; i++){
        if(a[i]==0)break;//corta el ciclo cuando el arreglo no tiene mas valores validos;
        acc2 = acc2 + pow(a[i], 2) - acc;
    }

    return acc2;
}
