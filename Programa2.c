#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <time.h>  

#define N 1000000


int calcular(char *a);

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
            
            
            printf("%f\n",calcular(F));
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

int calcular(char *a){
    int acc = 0;

    for(size_t i = 0; i < N - 1; i++)
    {
       char tmp = a[i] ^ a[i + 1];
       acc = acc + tmp;
    }

    return acc;
}
