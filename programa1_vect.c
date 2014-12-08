#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>

#include <stdio.h>
#include "cargarchivo.h"
#include <math.h>

#define N 400

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


float calcular(float *a, float *b);

int main(int argc, char *argv[])
{
    float a[N] __attribute__((aligned(16)));
    float b[N] __attribute__((aligned(16)));
    
    // NO hago entrada ahora, solamente números sin significado, usted debe
    // hacer que el programa lea esto desde un archivo
    int i;
    for(i = 0; i < N; i++){
        a[i] = i + 2;
    }
    
    for(i = 0; i < N; i++){
        b[i] = i + 2;
    }
    
    printf("%f\n", calcular(a, b));
    
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
        
        Vb=_mm_load_ps(&b[i]);
        sqrtVb= _mm_sqrt_ps(Vb);
        
        Ai_2 = _mm_div_ps(Va, _mm_set1_ps(2.));
        

        Vsum = _mm_add_ps(Vsum, Ai_2);
        Vsum = _mm_add_ps(Vsum,sqrtVb);

    }

    acc=Vsum[0]+Vsum[1]+Vsum[2]+Vsum[3];
    printf("%f\n", acc);
    
    for(i = 0; i < N; i+=4){
        Va=_mm_load_ps(&a[i]);
        Vsum2 = _mm_add_ps(Vsum2, _mm_sub_ps(_mm_mul_ps(Va, Va), _mm_set1_ps(acc)));
    }
    _mm_store_ps(acc2, Vsum2);
    return acc2[0]+acc2[1]+acc2[2]+acc2[3];
}

