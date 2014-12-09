#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <math.h>

#define N 30

float modulo(float *a){
    float suma = 0;
    float multip = 1;
    float elModulo;
    int i;

    for (/*size_t*/ i = 0; i < N; i++){
        multip =a[i]*a[i];
        suma = suma + multip;
    }

    elModulo = sqrt(suma);
    printf("el modulo es: %f\n", elModulo);
    return elModulo;
}

float sumar(float *a){
    float suma=0;
    float multip;
    float elModulo = modulo(a);
    int i;
    float cont=0;
    for (/*size_t*/ i = 0; i < N; i++){
        if(i<elModulo){
            multip = a[i]*a[i+1];
            suma = suma + multip;
            cont++;
        }
    }

    return suma;
}

int main(int argc, char *argv[])
{
	clock_t start = clock(); 
    int index;
    int c;
    
    opterr = 0;
    
    while ((c = getopt (argc, argv, "f:")) != -1)
        switch (c)
    {
        case 'f':
            printf("Leyendo archivo[%s]...\n", optarg);
            float *F=leerArchivo(optarg);
            
            
            printf("%f\n",sumar(F));
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
    

    printf("\nTiempo transcurrido: %f", ((double)clock() - start) / CLOCKS_PER_SEC);
    return 0;
}