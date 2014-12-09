#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h> /* for getopt */

#include "cargarchivo.h"

#define N 100000//de preferencia un numero multiplo de 4


float modulo(float a[]);
float sumar(float a[]);
int _mm_compare_ps(__m128 a, __m128 b);

int main(int argc, char *argv[])
{
    printf("el texto\n");
    float a[N] __attribute__((aligned(16)));
    int aflag = 0;
    int bflag = 0;
    char *cvalue = NULL;
    int index;
    int c;
    int i;
    
    opterr = 1;
    
    while ((c = getopt (argc, argv, "f:")) != -1)
        switch (c)
    {
        case 'f':
            printf("Leyendo archivo[%s]...\n", optarg);
            float *F=leerArchivo(optarg);
            //for (i; F[i]!=0; i++) printf("i  |  %f\n",F[i]);
            float valores[N];
            for (i; F[i]!=0; i++) valores[i]=F[i];
            printf("%f\n",sumar(valores));
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
    
    return 0;
}

float modulo(float a[]){
    float suma[4] __attribute__((aligned(16)))={0,0,0,0};
    __m128 sum = _mm_set1_ps(0);
    __m128 vector =_mm_set1_ps(0);
    int i;
    printf("%.1f %.1f %.1f %.1f\n",a[0],a[1],a[2],a[3] );
    for( i = 0; i < N; i+=4){
        vector = _mm_load_ps(&a[i]);
        //printf("%.1f %.1f %.1f %.1f\n",vector[0],vector[1],vector[2],vector[3] );
        if(_mm_compare_ps(vector,_mm_set1_ps(0)))break;
        sum=_mm_add_ps(sum, _mm_mul_ps(vector, vector));

    }
    _mm_store_ps(suma,sum);
    printf("el modulo es: %f\n", sqrt(suma[0]+suma[1]+suma[2]+suma[3]));
    return sqrt(suma[0]+suma[1]+suma[2]+suma[3]);
}

float sumar(float a[] ){
    float suma[4];
    float b[N] __attribute__((aligned(16)));
    int i;
    for(i=0;i<N-1;i++)b[i]=a[i-1];//el desface tuve que hacerlo aqui ya que no me dejaba tomar desde &a[i+1]
    __m128 sum = _mm_set1_ps(0);
    __m128 v1;
    __m128 v2;
    //for (i=0; i<10; i++) printf("i  |  %f\n",a[i]);

    float elModulo = modulo(a);


    for (i = 0; i < N; i+=4){
        if (i<elModulo) {
            v1=_mm_add_ps(_mm_set1_ps(0),_mm_load_ps(&a[i]));
            v2=_mm_load_ps(&b[i]);
            if(_mm_compare_ps(v1,_mm_set1_ps(0)))break;
            sum= _mm_add_ps(sum,_mm_mul_ps(v1, v2));
        }
    }
    _mm_store_ps(suma, sum);
    
    return suma[0]+suma[1]+suma[2]+suma[3];
}
 int _mm_compare_ps(__m128 a, __m128 b){//funcion que compara uno a uno los elementos en un vector
    a=_mm_sub_ps(a, b);
    float f[4] __attribute__((aligned(16)));
    _mm_store_ps(f, a);
    int r=((f[0]+f[1]+f[2]+f[3])==0);
    return r;//la hicimos porque no encontramos una que hiciera esto exactamente
}