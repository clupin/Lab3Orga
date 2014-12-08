#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include "cargarchivo.h"
#include <stdio.h>
#include <stdio.h>
#include <math.h>

#define N 40//de preferencia un numero multiplo de 4


float modulo(float a[]){
    float suma[4] __attribute__((aligned(16)))={0,0,0,0};
    __m128 sum = _mm_set1_ps(0);
    __m128 vector =_mm_set1_ps(0);
    int i;
    for( i = 0; i < N; i+=4){
        vector = _mm_load_ps(&a[i]);
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
    float elModulo = modulo(a);

    for (/*size_t*/ i = 0; i < N; i+=4){
        if (i<elModulo) {
            v1=_mm_add_ps(_mm_set1_ps(0),_mm_load_ps(&a[i]));
            v2=_mm_load_ps(&b[i]);
            sum= _mm_add_ps(sum,_mm_mul_ps(v1, v2));
        }
    }
    _mm_store_ps(suma, sum);
    
    return suma[0]+suma[1]+suma[2]+suma[3];
}

int main(int argc, char *argv[])
{
    printf("el texto\n");
    float a[N] __attribute__((aligned(16)));
    int i;
    //"inicializacion" del arreglo
    /*for(/*size_t i = 0; i < N; i++){
     a[i] = i + 1;
     }*/
    a[0]= 5.; a[1]= 3.; a[2]= 5.; a[3]= 5.; a[4]=1.; a[5]= 2.; a[6]= 1.; a[7]= 1.; a[8]= 1.; a[9]= 5.;
    a[10]= 3.; a[11]= 1.; a[12]= 3.; a[13]= 4.; a[14]=1.; a[15]= 4.; a[16]= 1.; a[17]= 2.; a[18]= 5.; a[19]= 4.;
    a[20]= 2.; a[21]= 5.; a[22]= 1.; a[23]= 4.; a[24]=4.; a[25]= 4.; a[26]= 5.; a[27]= 2.; a[28]= 2.; a[29]= 3.;
    
    printf("%f\n", sumar(a));
    
    return 0;
}