#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>

#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "cargarchivo.h"
#include <time.h>

#include <ctype.h>

#include <stdlib.h>

#include <unistd.h> /* for getopt */

#define N 4000000


int calcular(char *a);
__m128i _mm_powi(__m128i a, __m128i b);//protoripo de funcion implementada por nosotros.

int main(int argc, char *argv[])
{
    clock_t start = clock(); 
    char a[N] __attribute__((aligned(16)));
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
            
            archivo = fopen(optarg,"r");
            
            if(archivo == NULL){
                printf("\nError al abrir el archivo");
            } else {
                while (feof(archivo)==0){
                    a[i] = fgetc(archivo);
                    mensaje = fgetc(archivo);
                    i++;
                }
            }
            fclose(archivo);
            
            printf("%d\n",calcular(a));
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
    __m128i Va,Vb,acum=_mm_set1_epi32(0);
    int i;
    for(i = 0; i < N - 1; i+=4)
    {
        Va=_mm_setr_epi32(a[i], a[i+1], a[i+2], a[i+3]);
        Vb=_mm_setr_epi32(a[i+1], a[i+2], a[i+3], a[i+4]);
        
        acum = _mm_add_epi32(acum, _mm_powi(Va, Vb));
        
    }
    int32_t *intAcum = (int32_t*) &acum;
    return intAcum[0]+intAcum[1]+intAcum[2]+intAcum[3]-a[N];
}

__m128i _mm_powi(__m128i a, __m128i b){//eleva a[i]^b[i] sin excepciones, pero no de forma paralela
    int32_t *intA = (int32_t*) &a;
    int32_t *intB = (int32_t*) &b;
    int r1,r2,r3,r4;
    r1=intA[0]^intB[0];
    r2=intA[1]^intB[1];
    r3=intA[2]^intB[2];
    r4=intA[3]^intB[3];
    
    __m128i reslt=_mm_setr_epi32(r1,r2,r3,r4);
    return reslt;
}