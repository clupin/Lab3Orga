#include <stdio.h>
#include <malloc.h>
#include <stdio.h>

#define N 1000000


int calcular(char *a);
__m128 _mm_pow2_ps(__m128 a, __m128 b);//protoripo de funcion implementada por nosotros.

int main(int argc, char *argv[])
{
    char a[N];

    // NO hago entrada ahora, solamente números sin significado
    for(size_t i = 0; i < N; i++){
        a[i] = i % 120 + 1;
    }

    printf("%d\n", calcular(a));
    
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
