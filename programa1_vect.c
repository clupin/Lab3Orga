#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <time.h>  
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h> /* for getopt */

#include "cargarchivo.h"

#define N 100000//

__m128 _mm_pow2_ps(__m128 a, __m128 b);


float calcular(float *a, float *b);
int _mm_compare_ps(__m128 a, __m128 b);

int main(int argc, char *argv[])
{
    clock_t start = clock();
    float a[N] __attribute__((aligned(16)));
    float b[N] __attribute__((aligned(16)));
    int index;
    int c;
    int i;
    for(i = 0; i < N; i++)a[i] = i + 1;
    
    for(i = 0; i < N; i++) b[i] = i + 1;
    

    opterr = 0;
    
    while ((c = getopt (argc, argv, "f:")) != -1)
        switch (c)
    {
        case 'f':
            printf("Leyendo archivo[%s]...\n", optarg);
            float *F=leerArchivo(optarg);
            //for (i; F[i]!=0; i++) printf("i  |  %f\n",F[i]);
            int i;
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
    
    printf("Tiempo transcurrido: %f", ((double)clock() - start) / CLOCKS_PER_SEC)
    return 0;
}

float calcular(float *a, float *b){
    
    float acc;
    float acc2[4];
    
    /*for(size_t i = 0; i < N; i++){
        acc = acc + a[i] / 2 + sqrt(b[i]);
    }*/
    __m128 Va,Vb,Vsum,Vsum2;
    __m128 Ai_2,sqrtVb;
    int i;
    for(i = 0; i < N; i+=4){
        Va=_mm_load_ps(&a[i]);
        if(_mm_compare_ps(Va,_mm_set1_ps(0)))break;
        Vb=_mm_load_ps(&b[i]);
        sqrtVb= _mm_sqrt_ps(Vb);
        
        Ai_2 = _mm_div_ps(Va, _mm_set1_ps(2.));
        

        Vsum = _mm_add_ps(Vsum, Ai_2);
        Vsum = _mm_add_ps(Vsum,sqrtVb);
        printf("%f\n", Vsum[0]+Vsum[1]+Vsum[2]+Vsum[3]);
    }

    acc=Vsum[0]+Vsum[1]+Vsum[2]+Vsum[3];
    printf("%f\n", acc);
    
    for(i = 0; i < N; i+=4){
        Va=_mm_load_ps(&a[i]);
        if(_mm_compare_ps(Va,_mm_set1_ps(0)))break;
        Vsum2 = _mm_add_ps(Vsum2, _mm_sub_ps(_mm_mul_ps(Va, Va), _mm_set1_ps(acc)));
    }
    _mm_store_ps(acc2, Vsum2);
    return acc2[0]+acc2[1]+acc2[2]+acc2[3];
}
__m128 _mm_pow2_ps(__m128 a, __m128 b){//eleva a[i]^b[i] sin excepciones, pero no de forma paralela
    float base[4] __attribute__((aligned(16)));
    _mm_store_ps(base, a);
    float exponente[4] __attribute__((aligned(16)));
    _mm_store_ps(exponente, b);
    return _mm_setr_ps(
                       (b[0]==0)?0:powf(base[0], exponente[0]),
                       (b[1]==0)?0:powf(base[1], exponente[1]),
                       (b[2]==0)?0:powf(base[2], exponente[2]),
                       (b[3]==0)?0:powf(base[3], exponente[3]));
}

int _mm_compare_ps(__m128 a, __m128 b){//funcion que compara uno a uno los elementos en un vector
    a=_mm_sub_ps(a, b);
    float f[4] __attribute__((aligned(16)));
    _mm_store_ps(f, a);
    int r=((f[0]+f[1]+f[2]+f[3])==0);
    return r;//la hicimos porque no encontramos una que hiciera esto exactamente
}